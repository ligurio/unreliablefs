#ifndef ERRNO_HH
#define ERRNO_HH

#include <errno.h>

static const int errno_access[] = {
    EACCES,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EROFS,
    EFAULT,
    EINVAL,
    EIO,
    ENOMEM,
    ETXTBSY,
};

static const int errno_chmod[] = {
    EACCES,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_creat[] = {
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    EISDIR,
    ELOOP,
    EMFILE,
    ENAMETOOLONG,
    ENFILE,
    ENODEV,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    ENXIO,
    EOPNOTSUPP,
    EOVERFLOW,
    EPERM,
    EROFS,
    ETXTBSY,
    EWOULDBLOCK,
};

static const int errno_ftruncate[] = {
    EACCES,
    EBADF,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOTDIR,
    EPERM,
    EROFS,
    ETXTBSY,
};

static const int errno_link[] = {
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EIO,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
    EXDEV,
};

static const int errno_mkdir[] = {
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINVAL,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_mknod[] = {
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS ,
};

static const int errno_opendir[] = {
    EACCES,
    EBADF,
    EMFILE,
    ENOENT,
    ENOMEM,
    ENOTDIR,
};

static const int errno_readdir[] = {
    EBADF,
};

static const int errno_read[] = {
    EAGAIN,
    EWOULDBLOCK,
    EBADF,
    EFAULT,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
};

static const int errno_readlink[] = {
    EACCES,
    EFAULT,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
};

static const int errno_rename[] = {
    EACCES,
    EBUSY,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINVAL,
    EISDIR,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    ENOTEMPTY,
    EPERM,
    EROFS,
};

static const int errno_rmdir[] = {
    EACCES,
    EBUSY,
    EFAULT,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    ENOTEMPTY,
    EPERM,
    EROFS,
};

static const int errno_symlink[] = {
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_truncate[] = {
    EACCES,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS,
    ETXTBSY,
};

static const int errno_unlink[] = {
    EACCES,
    EBUSY,
    EFAULT,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
};

static const int errno_write[] = {
    EAGAIN,
    EWOULDBLOCK,
    EBADF,
    EDESTADDRREQ,
    EDQUOT,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    ENOSPC,
    EPERM,
    EPIPE,
};

static const int errno_lstat[] = {
    EACCES,
    EBADF,
    EFAULT,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EOVERFLOW,
};

static const int errno_statfs[] = {
    EACCES,
    EFAULT,
    EINTR,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSYS,
    ENOTDIR,
    EOVERFLOW,
};

static const int errno_close[] = {
    EBADF,
    EDQUOT,
    EINTR,
    EIO,
    ENOSPC,
};

static const int errno_utimensat[] = {
    EACCES,
    EBADF,
    EFAULT,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS,
    ESRCH,
};

static const int errno_fsync[] = {
    EBADF,
    EDQUOT,
    EINVAL,
    EIO,
    ENOSPC,
    EROFS,
};

static const int errno_setxattr[] = {
    EDQUOT,
    EEXIST,
    ENODATA,
    ENOSPC,
    ENOTSUP,
    EPERM,
    ERANGE,
    /* In addition, the errors documented in stat(2) can also occur: */
    EACCES,
    EBADF,
    EFAULT,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EOVERFLOW,
};

static const int errno_getxattr[] = {
    E2BIG,
    ENODATA,
    ENOTSUP,
    ERANGE,
    /* In addition, the errors documented in stat(2) can also occur: */
    EACCES,
    EBADF,
    EFAULT,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EOVERFLOW,
};

static const int errno_listxattr[] = {
    E2BIG,
    ENOTSUP,
    ERANGE,
    /* In addition, the errors documented in stat(2) can also occur: */
    EACCES,
    EBADF,
    EFAULT,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EOVERFLOW,
};

static const int errno_removexattr[] = {
    ENODATA,
    ENOTSUP,
    /* In addition, the errors documented in stat(2) can also occur: */
    EACCES,
    EBADF,
    EFAULT,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EOVERFLOW,
};

static int errno_flock[] = {
    EBADF,
    EINTR,
    EINVAL,
    ENOLCK,
    EWOULDBLOCK,
};

static int errno_fallocate[] = {
    EBADF,
    EFBIG,
    EINTR,
    EINVAL,
    EIO,
    ENODEV,
    ENOSPC,
    ENOSYS,
    EOPNOTSUPP,
    EPERM,
    ESPIPE,
    ETXTBSY,
};

static int errno_ioctl[] = {
    EBADF,
    EFAULT,
    EINVAL,
    ENOTTY,
};

static const int errno_fcntl[] = {
    EACCES,
    EAGAIN,
    EBADF,
    EBUSY,
    EDEADLK,
    EFAULT,
    EINTR,
    EINVAL,
    EMFILE,
    ENOLCK,
    ENOTDIR,
    EPERM,
};

#endif /* ERRNO_HH */
