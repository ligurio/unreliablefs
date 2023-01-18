#!/usr/bin/env python3

if __name__ == '__main__':
    import pytest
    import sys
    sys.exit(pytest.main([__file__] + sys.argv[1:]))

import binascii
import fcntl
import subprocess
import os
import sys
import shutil
import pytest
import stat
import shutil
import subprocess
import filecmp
import errno
from contextlib import contextmanager
from tempfile import NamedTemporaryFile
from util import (wait_for_mount, umount, cleanup, base_cmdline,
                  basedir, fuse_test_marker, safe_sleep)
from os.path import join as pjoin

def is_no_xattr_support():
    return sys.platform.startswith("freebsd") or \
            sys.platform == "openbsd"

no_xattr_support = is_no_xattr_support()

TEST_FILE = __file__

pytestmark = fuse_test_marker()

with open(TEST_FILE, 'rb') as fh:
    TEST_DATA = fh.read()

def name_generator(__ctr=[0]):
    __ctr[0] += 1
    return 'testfile_%d' % __ctr[0]


@pytest.mark.uses_fuse
@pytest.fixture(scope="function")
def setup_unreliablefs(tmpdir):
    mnt_dir = str(tmpdir.mkdir('mnt'))
    src_dir = str(tmpdir.mkdir('src'))

    options = "-basedir={}".format(src_dir)
    cmdline = base_cmdline + [ pjoin(basedir, 'build/unreliablefs/unreliablefs'), mnt_dir, options ]
    mount_process = subprocess.Popen(cmdline)
    wait_for_mount(mount_process, mnt_dir)

    yield mnt_dir, src_dir

    umount(mount_process, mnt_dir)
    cleanup(mount_process, mnt_dir)

@contextmanager
def os_open(name, flags):
    fd = os.open(name, flags)
    try:
        yield fd
    finally:
        os.close(fd)

def os_create(name):
    os.close(os.open(name, os.O_CREAT | os.O_RDWR))

def test_unlink(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    fullname = mnt_dir + "/" + name
    with open(pjoin(src_dir, name), 'wb') as fh:
        fh.write(b'hello')
    assert name in os.listdir(mnt_dir)
    os.unlink(fullname)
    with pytest.raises(OSError) as exc_info:
        os.stat(fullname)
    assert exc_info.value.errno == errno.ENOENT
    assert name not in os.listdir(mnt_dir)
    assert name not in os.listdir(src_dir)

def test_mkdir(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    dirname = name_generator()
    fullname = mnt_dir + "/" + dirname
    os.mkdir(fullname)
    fstat = os.stat(fullname)
    assert stat.S_ISDIR(fstat.st_mode)
    assert os.listdir(fullname) ==  []
    assert fstat.st_nlink in (1,2)
    assert dirname in os.listdir(mnt_dir)

def test_rmdir(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    fullname = mnt_dir + "/" + name
    os.mkdir(pjoin(src_dir, name))
    assert name in os.listdir(mnt_dir)
    os.rmdir(fullname)
    with pytest.raises(OSError) as exc_info:
        os.stat(fullname)
    assert exc_info.value.errno == errno.ENOENT
    assert name not in os.listdir(mnt_dir)
    assert name not in os.listdir(src_dir)

def test_symlink(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    linkname = name_generator()
    link_path = os.path.join(mnt_dir, linkname)

    targetname = name_generator()
    target_path = os.path.join("/tmp", targetname)
    with open(target_path, 'w+'):
        pass
    assert os.path.exists(target_path)

    os.symlink(target_path, link_path)
    fstat = os.lstat(link_path)
    assert stat.S_ISLNK(fstat.st_mode)
    assert os.readlink(link_path) == target_path
    assert fstat.st_nlink == 1
    assert linkname in os.listdir(mnt_dir)

def test_create(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    fullname = pjoin(mnt_dir, name)
    with pytest.raises(OSError) as exc_info:
        os.stat(fullname)
    assert exc_info.value.errno == errno.ENOENT
    assert name not in os.listdir(mnt_dir)

    fd = os.open(fullname, os.O_CREAT | os.O_RDWR)
    os.close(fd)

    assert name in os.listdir(mnt_dir)
    fstat = os.lstat(fullname)
    assert stat.S_ISREG(fstat.st_mode)
    assert fstat.st_nlink == 1
    assert fstat.st_size == 0

@pytest.mark.xfail(reason="gh-39")
def test_chown(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    filename = pjoin(mnt_dir, name_generator())
    os.mkdir(filename)
    fstat = os.lstat(filename)
    uid = fstat.st_uid
    gid = fstat.st_gid

    uid_new = uid + 1
    os.chown(filename, uid_new, -1)
    fstat = os.lstat(filename)
    assert fstat.st_uid == uid_new
    assert fstat.st_gid == gid

    gid_new = gid + 1
    os.chown(filename, -1, gid_new)
    fstat = os.lstat(filename)
    assert fstat.st_uid == uid_new
    assert fstat.st_gid == gid_new

def test_open_read(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    with open(pjoin(src_dir, name), 'wb') as fh_out, \
         open(TEST_FILE, 'rb') as fh_in:
        shutil.copyfileobj(fh_in, fh_out)
    assert len(os.listdir(mnt_dir)) == 1

    assert filecmp.cmp(pjoin(mnt_dir, name), TEST_FILE, False)

def test_open_write(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    content = b'AABBCC'
    fd = os.open(pjoin(src_dir, name),
                 os.O_CREAT | os.O_RDWR)
    os.write(fd, content)
    os.close(fd)

    fullname = pjoin(mnt_dir, name)
    with open(fullname, 'rb') as fh:
        assert fh.read() == content

@pytest.mark.xfail(sys.platform.startswith("freebsd"), reason="gh-44")
def test_append(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    os_create(pjoin(src_dir, name))
    fullname = pjoin(mnt_dir, name)
    with os_open(fullname, os.O_WRONLY) as fd:
        os.write(fd, b'foo\n')
    with os_open(fullname, os.O_WRONLY|os.O_APPEND) as fd:
        os.write(fd, b'bar\n')

    with open(fullname, 'rb') as fh:
        assert fh.read() == b'foo\nbar\n'

@pytest.mark.xfail(sys.platform.startswith("freebsd"), reason="gh-42")
def test_seek(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    os_create(pjoin(src_dir, name))
    fullname = pjoin(mnt_dir, name)
    with os_open(fullname, os.O_WRONLY) as fd:
        os.lseek(fd, 1, os.SEEK_SET)
        os.write(fd, b'foobar\n')
    with os_open(fullname, os.O_WRONLY) as fd:
        os.lseek(fd, 4, os.SEEK_SET)
        os.write(fd, b'com')

    with open(fullname, 'rb') as fh:
        assert fh.read() == b'\0foocom\n'

def test_open_unlink(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    name = pjoin(mnt_dir, name_generator())
    data1 = b'foo'
    data2 = b'bar'
    fullname = pjoin(mnt_dir, name)
    with open(fullname, 'wb+', buffering=0) as fh:
        fh.write(data1)
        os.unlink(fullname)
        with pytest.raises(OSError) as exc_info:
            os.stat(fullname)
            assert exc_info.value.errno == errno.ENOENT
        assert name not in os.listdir(mnt_dir)
        fh.write(data2)
        fh.seek(0)
        assert fh.read() == data1+data2

def test_open_gh_14(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    name = pjoin(mnt_dir, name_generator())
    fullname = pjoin(mnt_dir, name)

    with open(fullname, "w+") as fh:
        hs = "123456789ABCDEF1"
        hb = binascii.a2b_hex(hs)
        fh.write(str(hb))
        fh.seek(0)
        fh.read()

def test_statvfs(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    os.statvfs(mnt_dir)

def test_link(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    name1 = pjoin(mnt_dir, name_generator())
    name2 = pjoin(mnt_dir, name_generator())
    shutil.copyfile(TEST_FILE, name1)
    assert filecmp.cmp(name1, TEST_FILE, False)

    fstat1 = os.lstat(name1)
    assert fstat1.st_nlink == 1

    os.link(name1, name2)

    fstat1 = os.lstat(name1)
    fstat2 = os.lstat(name2)
    for attr in ('st_mode', 'st_dev', 'st_uid', 'st_gid',
                 'st_size', 'st_atime', 'st_mtime', 'st_ctime'):
        assert getattr(fstat1, attr) == getattr(fstat2, attr)
    assert os.path.basename(name2) in os.listdir(mnt_dir)
    assert filecmp.cmp(name1, name2, False)

    os.unlink(name2)

    assert os.path.basename(name2) not in os.listdir(mnt_dir)
    with pytest.raises(FileNotFoundError):
        os.lstat(name2)

    os.unlink(name1)

def test_readdir(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    newdir = name_generator()
    src_newdir = pjoin(src_dir, newdir)
    mnt_newdir = pjoin(mnt_dir, newdir)
    file_ = src_newdir + "/" + name_generator()
    subdir = src_newdir + "/" + name_generator()
    subfile = subdir + "/" + name_generator()

    os.mkdir(src_newdir)
    shutil.copyfile(TEST_FILE, file_)
    os.mkdir(subdir)
    shutil.copyfile(TEST_FILE, subfile)

    listdir_is = os.listdir(mnt_newdir)
    listdir_is.sort()
    listdir_should = [ os.path.basename(file_), os.path.basename(subdir) ]
    listdir_should.sort()
    assert listdir_is == listdir_should

    os.unlink(file_)
    os.unlink(subfile)
    os.rmdir(subdir)
    os.rmdir(src_newdir)

def test_readdir_big(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs

    # Add enough entries so that readdir needs to be called
    # multiple times.
    fnames = []
    for i in range(500):
        fname  = ('A rather long filename to make sure that we '
                  'fill up the buffer - ' * 3) + str(i)
        with open(pjoin(src_dir, fname), 'w') as fh:
            fh.write('File %d' % i)
        fnames.append(fname)

    listdir_is = sorted(os.listdir(mnt_dir))
    listdir_should = sorted(os.listdir(src_dir))
    assert listdir_is == listdir_should

    for fname in fnames:
        stat_src = os.stat(pjoin(src_dir, fname))
        stat_mnt = os.stat(pjoin(mnt_dir, fname))
        assert stat_src.st_mtime == stat_mnt.st_mtime
        assert stat_src.st_ctime == stat_mnt.st_ctime
        assert stat_src.st_size == stat_mnt.st_size
        os.unlink(pjoin(src_dir, fname))

def test_truncate_path(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    assert len(TEST_DATA) > 1024

    filename = pjoin(mnt_dir, name_generator())
    with open(filename, 'wb') as fh:
        fh.write(TEST_DATA)

    fstat = os.stat(filename)
    size = fstat.st_size
    assert size == len(TEST_DATA)

    # Add zeros at the end
    os.truncate(filename, size + 1024)
    assert os.stat(filename).st_size == size + 1024
    with open(filename, 'rb') as fh:
        assert fh.read(size) == TEST_DATA
        assert fh.read(1025) == b'\0' * 1024

    # Truncate data
    os.truncate(filename, size - 1024)
    assert os.stat(filename).st_size == size - 1024
    with open(filename, 'rb') as fh:
        assert fh.read(size) == TEST_DATA[:size-1024]

    os.unlink(filename)

def test_truncate_fd(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    assert len(TEST_DATA) > 1024
    with NamedTemporaryFile('w+b', 0, dir=mnt_dir) as fh:
        fd = fh.fileno()
        fh.write(TEST_DATA)
        fstat = os.fstat(fd)
        size = fstat.st_size
        assert size == len(TEST_DATA)

        # Add zeros at the end
        os.ftruncate(fd, size + 1024)
        assert os.fstat(fd).st_size == size + 1024
        fh.seek(0)
        assert fh.read(size) == TEST_DATA
        assert fh.read(1025) == b'\0' * 1024

        # Truncate data
        os.ftruncate(fd, size - 1024)
        assert os.fstat(fd).st_size == size - 1024
        fh.seek(0)
        assert fh.read(size) == TEST_DATA[:size-1024]

def test_passthrough(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    src_name = pjoin(src_dir, name)
    mnt_name = pjoin(src_dir, name)
    assert name not in os.listdir(src_dir)
    assert name not in os.listdir(mnt_dir)
    with open(src_name, 'w') as fh:
        fh.write('Hello, world')
    assert name in os.listdir(src_dir)
    assert name in os.listdir(mnt_dir)
    assert os.stat(src_name) == os.stat(mnt_name)

    name = name_generator()
    src_name = pjoin(src_dir, name)
    mnt_name = pjoin(src_dir, name)
    assert name not in os.listdir(src_dir)
    assert name not in os.listdir(mnt_dir)
    with open(mnt_name, 'w') as fh:
        fh.write('Hello, world')
    assert name in os.listdir(src_dir)
    assert name in os.listdir(mnt_dir)
    assert os.stat(src_name) == os.stat(mnt_name)

@pytest.mark.skipif(no_xattr_support, reason="no xattr support")
@pytest.mark.parametrize("symlink", (False, True))
def test_listxattr(setup_unreliablefs, symlink):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    src_name = pjoin(src_dir, name)
    mnt_name = pjoin(src_dir, name)
    os_create(mnt_name)
    linkname = name_generator()
    link_path = os.path.join(mnt_dir, linkname)
    os.symlink(mnt_dir, link_path)
    if symlink:
        target = link_path
    else:
        target = mnt_name

    attr1_name = b"user.aa"
    attr1_value = b"a"
    attr2_name = b"user.bb"
    attr2_value = b"b"

    num_attrs = len(os.listxattr(target))
    os.setxattr(target, attr1_name, attr1_value)
    assert attr1_name.decode("utf-8") in os.listxattr(target)
    os.setxattr(target, attr2_name, attr2_value)
    assert attr2_name.decode("utf-8") in os.listxattr(target)
    assert num_attrs + 2 == len(os.listxattr(target))

@pytest.mark.skipif(no_xattr_support, reason="no xattr support")
@pytest.mark.parametrize("symlink",
    (False,
     pytest.param(True, marks=pytest.mark.xfail(reason="gh-50")),
    ))
def test_getxattr(setup_unreliablefs, symlink):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    src_name = pjoin(src_dir, name)
    mnt_name = pjoin(src_dir, name)
    os_create(mnt_name)
    linkname = name_generator()
    link_path = os.path.join(mnt_dir, linkname)
    os.symlink(mnt_dir, link_path)
    if symlink:
        target = link_path
    else:
        target = mnt_name

    attr_value = b"unreliablefs"
    attr_name = b"user.fsname"

    os.setxattr(target, attr_name, attr_value)
    assert attr_name.decode("utf-8") in os.listxattr(target)
    assert os.getxattr(target, attr_name) == attr_value
    os.setxattr(target, attr_name, b"hello")
    assert os.getxattr(target, attr_name) == b"hello"

@pytest.mark.skipif(no_xattr_support, reason="no xattr support")
@pytest.mark.parametrize("symlink", (False, True))
def test_setxattr(setup_unreliablefs, symlink):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    src_name = pjoin(src_dir, name)
    mnt_name = pjoin(src_dir, name)
    os_create(mnt_name)
    linkname = name_generator()
    link_path = os.path.join(mnt_dir, linkname)
    os.symlink(mnt_dir, link_path)
    if symlink:
        target = link_path
    else:
        target = mnt_name

    attr_value = b"unreliablefs"
    attr_name = b"user.fsname"

    os.setxattr(target, attr_name, attr_value)
    assert attr_name.decode("utf-8") in os.listxattr(target)

@pytest.mark.skipif(no_xattr_support, reason="no xattr support")
@pytest.mark.parametrize("symlink",
    (pytest.param(True, marks=pytest.mark.xfail(reason="gh-50")),
     pytest.param(False, marks=pytest.mark.xfail(reason="gh-50")),
    ))
def test_removexattr(setup_unreliablefs, symlink):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    src_name = pjoin(src_dir, name)
    mnt_name = pjoin(mnt_dir, name)
    os_create(mnt_name)
    linkname = name_generator()
    link_path = os.path.join(mnt_dir, linkname)
    os.symlink(mnt_dir, link_path)
    if symlink:
        target = link_path
    else:
        target = mnt_name

    attr_value = b"unreliablefs"
    attr_name = b"user.fsname"

    os.setxattr(target, attr_name, attr_value)
    assert attr_name.decode("utf-8") in os.listxattr(target)
    assert os.getxattr(target, attr_name) == attr_value
    os.removexattr(target, attr_name)
    try:
        assert os.getxattr(target, attr_name) == None
    except OSError:
        pass

def test_flock(setup_unreliablefs):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    src_name = pjoin(src_dir, name)
    mnt_name = pjoin(src_dir, name)
    os_create(mnt_name)

    with open(mnt_name, 'w') as fh:
        fcntl.flock(fh, fcntl.LOCK_EX | fcntl.LOCK_NB)
        fcntl.flock(fh, fcntl.LOCK_UN)

@pytest.mark.parametrize("symlink", (False, True))
def test_utimens(setup_unreliablefs, symlink):
    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    src_name = pjoin(src_dir, name)
    mnt_name = pjoin(mnt_dir, name)
    os_create(mnt_name)
    linkname = name_generator()
    link_path = os.path.join(mnt_dir, linkname)
    os.symlink(mnt_name, link_path)
    if symlink:
        target = link_path
    else:
        target = mnt_name

    fstat = os.lstat(link_path)
    link_atime = fstat.st_atime
    link_mtime = fstat.st_mtime

    fstat = os.lstat(mnt_name)
    mnt_name_atime = fstat.st_atime + 10
    mnt_name_mtime = fstat.st_mtime + 10
    os.utime(target, (mnt_name_atime, mnt_name_mtime))

    fstat = os.lstat(mnt_name)
    assert fstat.st_atime == mnt_name_atime
    assert fstat.st_mtime == mnt_name_mtime

    if symlink:
        fstat = os.lstat(link_path)
        assert fstat.st_atime == link_atime
        assert fstat.st_mtime == link_mtime

@pytest.mark.long
def test_fsx(setup_unreliablefs):
    fsx_bin = shutil.which('fsx') or pjoin(basedir, 'build/unreliablefs/tests/fsx')
    if not fsx_bin:
        pytest.skip('fsx is required to execute testcase')

    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    src_name = pjoin(src_dir, name)
    mnt_name = pjoin(mnt_dir, name)
    os_create(mnt_name)
    cmd_line = '{} -N 10000 -d -W -c 4 {}'.format(fsx_bin, mnt_name)
    subprocess.check_call(cmd_line.split(' '))

@pytest.mark.long
def test_fio(setup_unreliablefs):
    if not shutil.which('fio'):
        pytest.skip('fio is required to execute testcase')

    mnt_dir, src_dir = setup_unreliablefs
    name = name_generator()
    src_name = pjoin(src_dir, name)
    mnt_name = pjoin(mnt_dir, name)
    os_create(mnt_name)
    cmd_line = "fio --name=random-write --ioengine=sync --rw=randwrite " \
                "--bs=1m --size=1G --numjobs=1 --iodepth=1 --runtime=60 " \
                "--time_based --end_fsync=1 --filename={}".format(mnt_name)
    subprocess.check_call(cmd_line.split(' '))
