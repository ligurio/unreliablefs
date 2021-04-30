## UnreliableFS

[![Build Status](https://api.cirrus-ci.com/github/ligurio/unreliablefs.svg)](https://cirrus-ci.com/github/ligurio/unreliablefs)

is a FUSE-based fault injection filesystem that allows to change
fault-injections in runtime.

Supported fault injections are:

- `errinj_noop` - replace file operation with no operation
  (similar to [libeatmydata](https://github.com/stewartsmith/libeatmydata),
  but applicable to any file operation).
- `errinj_kill_caller` - send SIGKILL to a process that invoked file operation.

### Building

Prerequisites:

- CentOS: `dnf install -y gcc -y cmake fuse fuse-devel`
- Ubuntu: `apt-get install -y gcc cmake fuse libfuse-dev`
- FreeBSD: `pkg install gcc cmake fusefs-libs pkgconf`
- OpenBSD: `pkg_add cmake`
- macOS: `brew install --cask osxfuse`

```sh
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j
```

### Using

```sh
$ mkdir /tmp/fs
$ unreliablefs /tmp/fs -base_dir=/tmp -seed=1618680646
$ cat << EOF > /tmp/fs/unreliablefs.conf
[errinj_noop]
op_regexp = .*
path_regexp = .*
probability = 30
EOF
$ ls -la
$ umount /tmp/fs
```
