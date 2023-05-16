# Change Log

All notable changes to this project will be documented in this file. This
change log follows the conventions of
[keepachangelog.com](https://keepachangelog.com/).

## [Unreleased]

[Unreleased]: https://github.com/ligurio/unreliablefs/compare/0.2.0...HEAD

### Added

- Initial version of a changelog.
- CodeQL integration.
- Testing on macOS on Github Actions.
- References to a section SEE ALSO in manual pages.
- CMake preset.

### Fixed

- Setting an arbitrary large duration values.
- Fix style warning in a manual page.
- Warnings produced by mandoc.
- FreeBSD setup in a Cirrus CI.
- Disabled tests on FreeBSD.
- Manual pages paths.

### Changed

- File layout in a project.
- Replace Ubuntu 21.04 with Ubuntu 20.04 (LTS) in a Cirrus CI.

### Removed

- Remove testing on macOS in a Cirrus CI.

## [0.2.0]

[0.2.0]: https://github.com/ligurio/unreliablefs/compare/0.1.0...HEAD

### Fixed

- Compilation with Clang 11 (#77).
- Compilation on FreeBSD 11 (#83).

### Added

- Use generic OS name in regression test suite (#78).
- Missed pytest.ini in regression test suite (#80).
- Lua rockspec (#88).

## [0.1.0]

### Added

- Support of configuration file that allows configuring faults in runtime (#3).
- Error injection `errinj_errno` - return error value and set random `errno` (#6).
- Error injection `errinj_kill_caller` - send `SIGKILL` to a process that invoked file operation (#28).
- Error injection `errinj_noop` - replace file operation with no operation (#18).
- Error injection `errinj_slowdown` - slowdown invoked file operation (#29).
- Continuous integration for macOS, Ubuntu Linux and FreeBSD.
- Manual pages for `unreliablefs(1)` and `unreliablefs.conf(5)`.
