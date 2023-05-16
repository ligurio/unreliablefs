## UnreliableFS

[![Build Status](https://api.cirrus-ci.com/github/ligurio/unreliablefs.svg)](https://cirrus-ci.com/github/ligurio/unreliablefs)

is a FUSE-based fault injection filesystem that allows to change
fault-injections in runtime using simple configuration file.

Supported fault injections are:

- `errinj_errno` - return error value and set random errno.
- `errinj_kill_caller` - send SIGKILL to a process that invoked file operation.
- `errinj_noop` - replace file operation with no operation
  (similar to [libeatmydata](https://github.com/stewartsmith/libeatmydata),
  but applicable to any file operation).
- `errinj_slowdown` - slowdown invoked file operation.

### Building

Prerequisites:

- CentOS: `dnf install -y gcc -y cmake fuse fuse-devel`
- Ubuntu: `apt-get install -y gcc cmake fuse libfuse-dev`
- FreeBSD: `pkg install gcc cmake fusefs-libs pkgconf`
- OpenBSD: `pkg_add cmake`
- macOS: `brew install --cask osxfuse`

```sh
$ cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build --parallel
```

### Packages

[![Packaging status](https://repology.org/badge/vertical-allrepos/fusefs:unreliablefs.svg)](https://repology.org/project/fusefs:unreliablefs/versions)

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

### Documentation

See documentation in [unreliablefs.1](https://ligurio.github.io/unreliablefs/unreliablefs.1.html) and
[unreliablefs.conf.5](https://ligurio.github.io/unreliablefs/unreliablefs.conf.5.html).

### License

MIT License, Copyright (c) 2020-2023, Sergey Bronnikov
BSD-3-Clause, Copyright (C) 2009-2020, Ben Hoyt
