#define FUSE_USE_VERSION 29

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "unreliablefs_ops.h"

static struct fuse_operations unreliable_ops = {
    .getattr     = unreliable_getattr,
    .readlink    = unreliable_readlink,
    .mknod       = unreliable_mknod,
    .mkdir       = unreliable_mkdir,
    .unlink      = unreliable_unlink,
    .rmdir       = unreliable_rmdir,
    .symlink     = unreliable_symlink,
    .rename      = unreliable_rename,
    .link        = unreliable_link,
    .chmod       = unreliable_chmod,
    .chown       = unreliable_chown,
    .truncate    = unreliable_truncate,
    .open	 = unreliable_open,
    .read	 = unreliable_read,
    .write       = unreliable_write,
    .statfs      = unreliable_statfs,
    .flush       = unreliable_flush,
    .release     = unreliable_release,
    .fsync       = unreliable_fsync,
#ifdef HAVE_XATTR
    .setxattr    = unreliable_setxattr,
    .getxattr    = unreliable_getxattr,
    .listxattr   = unreliable_listxattr,
    .removexattr = unreliable_removexattr,
#endif /* HAVE_XATTR */
    .opendir     = unreliable_opendir,
    .readdir     = unreliable_readdir,
    .releasedir  = unreliable_releasedir,
    .fsyncdir    = unreliable_fsyncdir,

    .init        = unreliable_init,
    .destroy     = unreliable_destroy,

    .access      = unreliable_access,
    .create      = unreliable_create,
    .ftruncate   = unreliable_ftruncate,
    .fgetattr    = unreliable_fgetattr,
    .lock        = unreliable_lock,
#if !defined(__OpenBSD__)
    .ioctl       = unreliable_ioctl,
#endif /* __OpenBSD__ */
#ifdef HAVE_FLOCK
    .flock       = unreliable_flock,
#endif /* HAVE_FLOCK */
#ifdef HAVE_FALLOCATE
    .fallocate   = unreliable_fallocate,
#endif /* HAVE_FALLOCATE */
#ifdef HAVE_UTIMENSAT
    .utimens     = unreliable_utimens,
#endif /* HAVE_UTIMENSAT */
};

int main(int argc, char *argv[])
{
#if defined(DEBUG)
    int fuse_argc = 3;
    char *fuse_argv[fuse_argc];

    if (argc != 2) {
	fprintf(stderr, "Usage: %s MOUNTPOINT\n", argv[0]);
	return EXIT_FAILURE;
    }

    fuse_argv[0] = argv[0];
    fuse_argv[1] = argv[1];
    #if FUSE_USE_VERSION < 30
	fuse_argv[2] = "-ononempty,suid,dev,allow_other,default_permissions";
    #else
	fuse_argv[2] = "-osuid,dev,allow_other,default_permissions";
    #endif
    fuse_argv[3] = NULL;

    fprintf(stdout, "Starting FUSE filesystem\n");
    return fuse_main(fuse_argc, fuse_argv, &unreliable_ops, NULL);
#else
    fprintf(stdout, "Starting FUSE filesystem\n");
    return fuse_main(argc, argv, &unreliable_ops, NULL);
#endif /* DEBUG */
}
