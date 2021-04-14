## UnreliableFS

[![Build Status](https://api.cirrus-ci.com/github/ligurio/unreliablefs.svg)](https://cirrus-ci.com/github/ligurio/unreliablefs)

is a FUSE-based fault injection filesystem.

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
$ ./build/unreliablefs ~/Downloads/mnt/ -omodules=subdir,subdir=/tmp
$ ls ~/Downloads/mnt/
$ umount /tmp/unreliable
```
