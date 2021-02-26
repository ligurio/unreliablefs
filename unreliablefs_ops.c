#define _GNU_SOURCE
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#if !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__APPLE__)
#include <sys/xattr.h>
#endif /* __OpenBSD__ */

#include "unreliablefs_errinj.h"
#include "unreliablefs_ops.h"

int unreliable_lstat(const char *path, struct stat *buf)
{
    int ret = error_inject(path, "lstat");
    if (ret) {
        return ret;
    }

    memset(buf, 0, sizeof(struct stat));
    if (lstat(path, buf) == -1) {
        return -errno;
    } else {
        return 0;
    }

    return -ENOENT;
}

int unreliable_getattr(const char *path, struct stat *buf)
{
    int ret = error_inject(path, "getattr");
    if (ret) {
        return ret;
    }

    memset(buf, 0, sizeof(struct stat));
    if (stat(path, buf) == -1) {
        return -errno;
    } else {
        return 0;
    }

    return -ENOENT;
}

int unreliable_readlink(const char *path, char *buf, size_t bufsiz)
{
    int ret = error_inject(path, "readlink");
    if (ret) {
        return ret;
    }

    ret = readlink(path, buf, bufsiz);
    if (ret == -1) {
        return -errno;
    }
    buf[ret] = 0;

    return 0;
}

int unreliable_mknod(const char *path, mode_t mode, dev_t dev)
{
    int ret = error_inject(path, "mknod");
    if (ret) {
        return ret;
    }

    ret = mknod(path, mode, dev);    
    if (ret == -1) {
        return -errno;
    }

    return 0;
}

int unreliable_mkdir(const char *path, mode_t mode)
{
    int ret = error_inject(path, "mkdir");
    if (ret) {
        return ret;
    }

    ret = mkdir(path, mode);
    if (ret == -1) {
        return -errno;
    }

    return 0;
}

int unreliable_unlink(const char *path)
{
    int ret = error_inject(path, "unlink");
    if (ret) {
        return ret;
    }

    ret = unlink(path); 
    if (ret == -1) {
        return -errno;
    }

    return 0;
}

int unreliable_rmdir(const char *path)
{
    int ret = error_inject(path, "rmdir");
    if (ret) {
        return ret;
    }

    ret = rmdir(path); 
    if (ret == -1) {
        return -errno;
    }

    return 0;
}

int unreliable_symlink(const char *target, const char *linkpath)
{
    int ret = error_inject(target, "symlink");
    if (ret) {
        return ret;
    }

    ret = symlink(target, linkpath);
    if (ret == -1) {
        return -errno;
    }

    return 0;
}

int unreliable_rename(const char *oldpath, const char *newpath)
{
    int ret = error_inject(oldpath, "rename");
    if (ret) {
        return ret;
    }

    ret = rename(oldpath, newpath);
    if (ret == -1) {
        return -errno;
    }

    return 0;
}

int unreliable_link(const char *oldpath, const char *newpath)
{
    int ret = error_inject(oldpath, "link");
    if (ret) {
        return ret;
    }

    ret = link(oldpath, newpath);
    if (ret < 0) {
        return -errno;
    }

    return 0;
}

int unreliable_chmod(const char *path, mode_t mode)
{
    int ret = error_inject(path, "chmod");
    if (ret) {
        return ret;
    }
    
    ret = chmod(path, mode);
    if (ret < 0) {
        return -errno;
    }

    return 0;
}

int unreliable_chown(const char *path, uid_t owner, gid_t group)
{
    int ret = error_inject(path, "chown");
    if (ret) {
        return ret;
    }

    ret = chown(path, owner, group);
    if (ret == -1) {
        return -errno;
    }

    return 0;
}

int unreliable_truncate(const char *path, off_t length)
{
    int ret = error_inject(path, "truncate");
    if (ret) {
        return ret;
    }

    ret = truncate(path, length); 
    if (ret == -1) {
        return -errno;
    }

    return 0;
}

int unreliable_open(const char *path, struct fuse_file_info *fi)
{
    int ret = error_inject(path, "open");
    if (ret) {
        return ret;
    }

    ret = open(path, fi->flags);
    if (ret == -1) {
        return -errno;
    }
    fi->fh = ret;

    return 0;
}

int unreliable_read(const char *path, char *buf, size_t size, off_t offset,
                    struct fuse_file_info *fi)
{
    int ret = error_inject(path, "read");
    if (ret) {
        return ret;
    }

    int fd;

    if (fi == NULL) {
	fd = open(path, O_RDONLY);
    } else {
	fd = fi->fh;
    }

    if (fd == -1) {
	return -errno;
    }

    ret = pread(fd, buf, size, offset);
    if (ret == -1) {
        ret = -errno;
    }

    if (fi == NULL) {
	close(fd);
    }

    return ret;
}

int unreliable_write(const char *path, const char *buf, size_t size,
                     off_t offset, struct fuse_file_info *fi)
{
    int ret = error_inject(path, "write");
    if (ret) {
        return ret;
    }

    int fd;
    (void) fi;
    if(fi == NULL) {
	fd = open(path, O_WRONLY);
    } else {
	fd = fi->fh;
    }

    if (fd == -1) {
	return -errno;
    }

    ret = pwrite(fd, buf, size, offset);
    if (ret == -1) {
        ret = -errno;
    }

    if(fi == NULL) {
        close(fd);
    }

    return ret;
}

int unreliable_statfs(const char *path, struct statvfs *buf)
{
    int ret = error_inject(path, "statfs");
    if (ret) {
        return ret;
    }

    ret = statvfs(path, buf);
    if (ret == -1) {
        return -errno;
    }

    return 0;
}

int unreliable_flush(const char *path, struct fuse_file_info *fi)
{
    int ret = error_inject(path, "flush");
    if (ret) {
        return ret;
    }

    ret = close(dup(fi->fh));
    if (ret == -1) {
        return -errno;
    }

    return 0;
}

int unreliable_release(const char *path, struct fuse_file_info *fi)
{
    int ret = error_inject(path, "release");
    if (ret) {
        return ret;
    }

    ret = close(fi->fh);
    if (ret == -1) {
        return -errno;
    }

    return 0;    
}

int unreliable_fsync(const char *path, int datasync, struct fuse_file_info *fi)
{
    int ret = error_inject(path, "fsync");
    if (ret) {
        return ret;
    }

    if (datasync) {
        ret = fdatasync(fi->fh);
        if (ret == -1) {
            return -errno;
        }
    } else {
        ret = fsync(fi->fh);
        if (ret == -1) {
            return -errno;
        }
    }

    return 0;
}

#if !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__APPLE__)
int unreliable_setxattr(const char *path, const char *name,
                        const char *value, size_t size, int flags)
{
    int ret = error_inject(path, "setxattr");
    if (ret) {
        return ret;
    }

    ret = setxattr(path, name, value, size, flags);
    if (ret == -1) {
        return -errno;
    }

    return 0;
}
#endif /* __OpenBSD__ */

#if !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__APPLE__)
int unreliable_getxattr(const char *path, const char *name,
                        char *value, size_t size)
{
    int ret = error_inject(path, "getxattr");
    if (ret) {
        return ret;
    }

    ret = getxattr(path, name, value, size);
    if (ret == -1) {
        return -errno;
    }
    
    return 0;
}
#endif /* __OpenBSD__ */

#if !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__APPLE__)
int unreliable_listxattr(const char *path, char *list, size_t size)
{
    int ret = error_inject(path, "listxattr");
    if (ret) {
        return ret;
    }

    ret = listxattr(path, list, size);
    if (ret == -1) {
        return -errno;
    }
    
    return 0;
}
#endif /* __OpenBSD__ */

#if !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__APPLE__)
int unreliable_removexattr(const char *path, const char *name)
{
    int ret = error_inject(path, "removexattr");
    if (ret) {
        return ret;
    }

    ret = removexattr(path, name);
    if (ret == -1) {
        return -errno;
    }
    
    return 0;    
}
#endif /* __OpenBSD__ */

int unreliable_opendir(const char *path, struct fuse_file_info *fi)
{
    int ret = error_inject(path, "opendir");
    if (ret) {
        return ret;
    }

    DIR *dir = opendir(path);

    if (!dir) {
        return -errno;
    }
    fi->fh = (int64_t) dir;

    return 0;    
}

int unreliable_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info *fi)
{
    int ret = error_inject(path, "readdir");
    if (ret) {
        return ret;
    }

    DIR *dp = (DIR *) fi->fh;
    struct dirent *de;

    (void) offset;
    (void) fi;

    while ((de = readdir(dp)) != NULL) {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
        if (filler(buf, de->d_name, &st, 0))
            break;
    }
    
    return 0;    
}

int unreliable_releasedir(const char *path, struct fuse_file_info *fi)
{
    int ret = error_inject(path, "releasedir");
    if (ret) {
        return ret;
    }

    DIR *dir = (DIR *) fi->fh;

    ret = closedir(dir);
    if (ret == -1) {
        return -errno;
    }
    
    return 0;    
}

int unreliable_fsyncdir(const char *path, int datasync, struct fuse_file_info *fi)
{
    int ret = error_inject(path, "fsyncdir");
    if (ret) {
        return ret;
    }

    DIR *dir = opendir(path);
    if (!dir) {
        return -errno;
    }

    if (datasync) {
        ret = fdatasync(dirfd(dir));
        if (ret == -1) {
            return -errno;
        }
    } else {
        ret = fsync(dirfd(dir));
        if (ret == -1) {
            return -errno;
        }
    }
    closedir(dir);

    return 0;
}

void *unreliable_init(struct fuse_conn_info *conn)
{
    return NULL;
}

void unreliable_destroy(void *private_data)
{

}

int unreliable_access(const char *path, int mode)
{
    int ret = error_inject(path, "access");
    if (ret) {
        return ret;
    }

    ret = access(path, mode); 
    if (ret == -1) {
        return -errno;
    }
    
    return 0;
}

int unreliable_create(const char *path, mode_t mode,
                      struct fuse_file_info *fi)
{
    int ret = error_inject(path, "create");
    if (ret) {
        return ret;
    }

    ret = creat(path, mode);
    if (ret == -1) {
        return -errno;
    }
    fi->fh = ret;

    return 0;    
}

int unreliable_ftruncate(const char *path, off_t length,
                         struct fuse_file_info *fi)
{
    int ret = error_inject(path, "ftruncate");
    if (ret) {
        return ret;
    }

    ret = truncate(path, length);
    if (ret == -1) {
        return -errno;
    }
    
    return 0;    
}

int unreliable_fgetattr(const char *path, struct stat *buf,
                        struct fuse_file_info *fi)
{
    int ret = error_inject(path, "fgetattr");
    if (ret) {
        return ret;
    }

    ret = fstat((int) fi->fh, buf);
    if (ret == -1) {
        return -errno;
    }
    
    return 0;    
}

int unreliable_lock(const char *path, struct fuse_file_info *fi, int cmd,
                    struct flock *fl)
{
    int ret = error_inject(path, "lock");
    if (ret) {
        return ret;
    }

    ret = fcntl((int) fi->fh, cmd, fl);
    if (ret == -1) {
        return -errno;
    }

    return 0;
}

#if !defined(__OpenBSD__)
int unreliable_ioctl(const char *path, int cmd, void *arg,
                     struct fuse_file_info *fi,
                     unsigned int flags, void *data)
{
    int ret = error_inject(path, "ioctl");
    if (ret) {
        return ret;
    }

    ret = ioctl(fi->fh, cmd, arg);
    if (ret == -1) {
        return -errno;
    }
    
    return 0;    
}
#endif /* __OpenBSD__ */

#if !defined(__OpenBSD__)
int unreliable_flock(const char *path, struct fuse_file_info *fi, int op)
{
    int ret = error_inject(path, "flock");
    if (ret) {
        return ret;
    }

    ret = flock(((int) fi->fh), op);
    if (ret == -1) {
        return -errno;
    }
    
    return 0;    
}
#endif /* __OpenBSD__ */

#if !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__APPLE__)
int unreliable_fallocate(const char *path, int mode,
                         off_t offset, off_t len,
                         struct fuse_file_info *fi)
{
    int ret = error_inject(path, "fallocate");
    if (ret) {
        return ret;
    }

    int fd;
    (void) fi;

    if (mode) {
	return -EOPNOTSUPP;
    }

    if(fi == NULL) {
	fd = open(path, O_WRONLY);
    } else {
	fd = fi->fh;
    }

    if (fd == -1) {
	return -errno;
    }

    ret = fallocate((int) fi->fh, mode, offset, len);
    if (ret == -1) {
        return -errno;
    }

    if(fi == NULL) {
	close(fd);
    }
    
    return 0;    
}
#endif /* __OpenBSD__ */
