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
- `errinj_1byte_read` - amount of data returned by `read()` call is always
  limited by a single byte.

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

See documentation in [unreliablefs.1](https://ligurio.github.io/unreliablefs/unreliablefs.1.html) and
[unreliablefs.conf.5](https://ligurio.github.io/unreliablefs/unreliablefs.conf.5.html).

### References

- "Can Applications Recover from fsync Failures?" - Anthony Rebello, Yuvraj
  Patel, Ramnatthan Alagappan, Andrea C. Arpaci-Dusseau and Remzi H.
- "All File Systems Are Not Created Equal: On the Complexity of Crafting
  Crash-Consistent Applications" - Thanumalayan Sankaranarayana Pillai, Vijay
  Chidambaram, Ramnatthan Alagappan, Samer Al-Kiswany, Andrea C.
  Arpaci-Dusseau, and Remzi H. Arpaci-Dusseau, University of Wisconsin–Madison
- "A survey on simulation-based fault injection tools for complex systems" -
  Maha Kooli, Giorgio Di Natale
- "To FUSE or Not to FUSE: Performance of User-Space File Systems" - Bharath
  Kumar Reddy Vangoor, Vasily Tarasov, Erez Zadok
- "Performance and Resource Utilization of FUSE User-Space File Systems"
  Bharath Kumar Reddy Vangoor, Prafful Agarwal, Manu Mathew, Arun Ramachandran,
  and Swaminathan Sivaraman, Vasily Tarasov, Erez Zadok.
- "Performance and Extension of User Space File Systems" - Aditya Rajgarhia, Ashish Gehani
- "Files are hard" - Dan Luu
- "Systematic Testing of Fault Handling Code in Linux Kernel" - Alexey
  Khoroshilov, Andrey Tsyvarev
- "Software-Based Fault Injection Framework For Storage Systems" - Vinod
  Eswaraprasad, Smitha Jayaram
- Many consumer-grade SSD drives can ignore disk flushes and falsely report to
  operating systems that data was written while it in fact was not. See [Virtuozzo Storage Documentation](https://docs.virtuozzo.com/virtuozzo_hybrid_server_7_installation_guide/preparing-for-installation/planning-storage-gui.html#planning-node-hardware-configurations) and [PostgreSQL Documentation](https://www.postgresql.org/docs/current/wal-reliability.html).

### Similar projects

- CuttleFS - FUSE-based file system with private page cache to simulate post fsync
  failure characteristics of modern file systems.
- libeatmydata - `LD_PRELOAD` library that disables all forms of writing data
  safely to disk. `fsync()` becomes a NO-OP, `O_SYNC` is removed etc.
- CharybdeFS - FUSE-based fault injection filesystem with a Thrift RPC
  interface for instrumentation.
- PetardFS - FUSE-based file system for injecting intentional errors.
- HookFS: A Usermode Hookable Filesystem Library.
