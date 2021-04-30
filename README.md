## UnreliableFS

[![Build Status](https://api.cirrus-ci.com/github/ligurio/unreliablefs.svg)](https://cirrus-ci.com/github/ligurio/unreliablefs)

is a FUSE-based fault injection filesystem that allows to change
fault-injections in runtime.

### Simulation of real errors

- https://danluu.com/file-consistency/
- see Phoebe https://github.com/gluckzhang/phoebe
- All File Systems Are Not Created Equal: On the Complexity of Crafting Crash-Consistent Applications
https://www.usenix.org/system/files/conference/osdi14/osdi14-paper-pillai.pdf
https://www.usenix.org/sites/default/files/conference/protected-files/osdi14_slides_pillai.pdf
- https://www.snia.org/sites/default/files/files2/files2/SDC2013/presentations/TestingMethodologies/VinodEswaraprasad_Software-Based_Fault-Storage-v1-0.pdf
- http://pages.cs.wisc.edu/~gibson/pdf/fault-injector.pdf
- A survey on simulation-based fault injection tools for complex systems
https://hal-auf.archives-ouvertes.fr/hal-01075473/document
- Describe a reasons to test with noop for `fsync(2)` [^1] and [^2]
- Eat My Data: How Everybody gets File IO Wrong
https://www.youtube.com/watch?v=LMe7hf2G1po
https://www.slideshare.net/nan1nan1/eat-my-data

[^1]: https://docs.virtuozzo.com/virtuozzo_hybrid_server_7_installation_guide/preparing-for-installation/planning-storage-gui.html#planning-node-hardware-configurations
[^2]: https://www.postgresql.org/docs/current/wal-reliability.html

Supported fault injections are:

- `errinj_noop` - replace file operation with no operation
  (similar to [libeatmydata](https://github.com/stewartsmith/libeatmydata),
  but applicable to any file operation).

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

### Performance

- [To FUSE or Not to FUSE: Performance of User-Space File Systems](https://www.usenix.org/conference/fast17/technical-sessions/presentation/vangoor)
- [Performance and Resource Utilization of FUSE User-Space File Systems](https://dl.acm.org/doi/fullHtml/10.1145/3310148)
- [Performance and Extension of User Space File Systems∗](https://core.ac.uk/download/pdf/193586624.pdf)
- TODO: `FUSE_PASSTHROUGH`, see https://lkml.org/lkml/2020/8/12/547
- TODO: https://chubaofs.readthedocs.io/en/latest/user-guide/fuse.html
