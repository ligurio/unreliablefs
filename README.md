## UnreliableFS

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
$ mkdir /tmp/unreliable
$ unreliablefs /tmp/unreliable
$ echo "UnreliableFS" > /tmp/example/tmp/info
$ cat /tmp/info 
UnreliableFS
$ umount /tmp/unreliable
```
