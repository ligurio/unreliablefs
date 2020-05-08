#include <errno.h>
#include <stdlib.h>

#if !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__APPLE__)
#define MAX_ERR EXFULL
#else
#define MAX_ERR ELAST
#endif /* __OpenBSD__ */
#define MIN_ERR E2BIG

#define PROBABILITY 5

static int rand_range(int min_n, int max_n)
{
    return rand() % (max_n - min_n + 1) + min_n;
}

int error_inject(const char* path, char* operation)
{
    int err_no = 0;
    int p = rand_range(0, 100);
    if ((p >= 0) && (p <= PROBABILITY)) {
        err_no = rand_range(MIN_ERR, MAX_ERR);
    }

    return -err_no;
}
