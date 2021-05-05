#ifndef ERRNO_HH
#define ERRNO_HH

#include <errno.h>

static const int errno_access[] = {
    EACCES,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EROFS,
    ETXTBSY,
};

static const int errno_chmod[] = {
    EACCES,
    EFAULT,
    EFTYPE,
    EINTEGRITY,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EPERM,
    EROFS,
};

static const int errno_creat[] = {
    EACCES,
    EBADF,
    ECAPMODE,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINTEGRITY,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    EMFILE,
    EMLINK,
    ENAMETOOLONG,
    ENFILE,
    ENOENT,
    ENOSPC,
    ENOTCAPABLE,
    ENOTDIR,
    ENXIO,
    EOPNOTSUPP,
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
    EINTEGRITY,
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

static const int errno_link[] = {
    EACCES,
    EBADF,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EOPNOTSUPP,
    EPERM,
    EROFS,
    EXDEV,
};

static const int errno_mkdir[] = {
    EACCES,
    EBADF,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINTEGRITY,
    EIO,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_mknod[] = {
    EACCES,
    EBADF,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_opendir[] = {
    EACCES,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
};

static const int errno_readdir[] = {
    EBADF,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
};

static const int errno_read[] = {
    EAGAIN,
    EBADF,
    EBUSY,
    ECONNRESET,
    EFAULT,
    EINTEGRITY,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    EOPNOTSUPP,
    EOVERFLOW,
};

static const int errno_readlink[] = {
    EACCES,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
};

static const int errno_rename[] = {
    EACCES,
    ECAPMODE,
    EDQUOT,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    ENOTEMPTY,
    EPERM,
    EROFS,
    EXDEV,
};

static const int errno_rmdir[] = {
    EACCES,
    EBUSY,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
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
    EINTEGRITY,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_truncate[] = {
    EACCES,
    EFAULT,
    EFBIG,
    EINTEGRITY,
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
    EFAULT,
    EINTEGRITY,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_write[] = {
    EAGAIN,
    EBADF,
    EDQUOT,
    EFAULT,
    EFBIG,
    EINTEGRITY,
    EINTR,
    EINVAL,
    EIO,
    ENOSPC,
    EPIPE,
    EROFS,
};

static const int errno_lstat[] = {
    EACCES,
    EFAULT,
    EINTEGRITY,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EOVERFLOW,
};

static const int errno_statfs[] = {
    EACCES,
    EFAULT,
    EINTEGRITY,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
};

static const int errno_close[] = {
    EBADF,
    EINTR,
    ENOSPC,
    ECONNRESET,
};

static const int errno_utimensat[] = {
    EACCES,
    EBADF,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
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
    EINTEGRITY,
    EINVAL,
    EIO,
};

static int errno_flock[] = {
    EBADF,
    EINVAL,
    ENOLCK,
    EOPNOTSUPP,
    EWOULDBLOCK,
};

static int errno_ioctl[] = {
    EBADF,
    EFAULT,
    EINVAL,
    ENOTTY,
};

static const int errno_fcntl[] = {
    EAGAIN,
    EBADF,
    EDEADLK,
    EINTR,
    EINVAL,
    EMFILE,
    ENOLCK,
    ENOTTY,
    EOPNOTSUPP,
    EOVERFLOW,
    EPERM,
    ESRCH,
};

#endif /* ERRNO_HH */
