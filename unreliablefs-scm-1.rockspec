package = 'unreliablefs'
version = 'scm-1'

description = {
    summary = "A FUSE-based fault injection filesystem",
    detailed = [[
    is a FUSE-based fault injection filesystem that allows to change
    fault-injections in runtime using simple configuration file.

    Supported fault injections are:

    - `errinj_errno` - return error value and set random errno;
    - `errinj_kill_caller` - send SIGKILL to a process that invoked file operation;
    - `errinj_noop` - replace file operation with no operation;
    - `errinj_slowdown` - slowdown invoked file operation;
    ]],
    homepage = "https://github.com/ligurio/unreliablefs",
    maintainer = "Sergey Bronnikov <estetus@gmail.com>",
    license = "MIT",
}

source  = {
    url = 'git+https://github.com/ligurio/unreliablefs.git',
    branch = 'master',
}

external_dependencies = {
    FUSE = {
        header = 'fuse.h',
    },
}

build = {
    type = 'cmake',
    copy_directories = {},
    variables = {
        CMAKE_INSTALL_PREFIX = "$(PREFIX)",
    },
}
