#define FUSE_USE_VERSION 29

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

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

struct unreliablefs_config {
     int seed;
     char *base_dir;
};

enum {
     KEY_HELP,
     KEY_VERSION,
};

#define UNRELIABLEFS_OPT(t, p, v) { t, offsetof(struct unreliablefs_config, p), v }
#define UNRELIABLEFS_VERSION "0.1"

static struct fuse_opt unreliablefs_opts[] = {
    UNRELIABLEFS_OPT("seed=%i",           seed, 0),
    UNRELIABLEFS_OPT("base_dir=%s",       base_dir, 0),

    FUSE_OPT_KEY("-V",             KEY_VERSION),
    FUSE_OPT_KEY("--version",      KEY_VERSION),
    FUSE_OPT_KEY("-h",             KEY_HELP),
    FUSE_OPT_KEY("--help",         KEY_HELP),
    FUSE_OPT_END
};

static int unreliablefs_opt_proc(void *data, const char *arg, int key, struct fuse_args *outargs)
{
    switch (key) {
    case KEY_HELP:
            fprintf(stderr,
                    "\n"
                    "UnreliableFS options:\n"
                    "    -o seed=NUM\n"
                    "    -o base_dir=STRING\n\n");
            fuse_opt_add_arg(outargs, "-h");
            fuse_main(outargs->argc, outargs->argv, &unreliable_ops, NULL);
            exit(1);

    case KEY_VERSION:
            fprintf(stderr, "UnreliableFS version %s\n", UNRELIABLEFS_VERSION);
            fuse_opt_add_arg(outargs, "--version");
            fuse_main(outargs->argc, outargs->argv, &unreliable_ops, NULL);
            exit(0);
    }
    return 1;
}

int main(int argc, char *argv[])
{
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    struct unreliablefs_config conf;

    memset(&conf, 0, sizeof(conf));

    fuse_opt_parse(&args, &conf, unreliablefs_opts, unreliablefs_opt_proc);
    /* fuse_opt_add_arg(&args, "-omodules=subdir,subdir=/tmp"); */
    fprintf(stdout, "Starting FUSE filesystem\n");
    fprintf(stdout, "Seed %d, base_dir %s\n", conf.seed, conf.base_dir);

    return fuse_main(args.argc, args.argv, &unreliable_ops, NULL);
}
