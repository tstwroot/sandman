#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/statvfs.h>

#define GB_FACTOR (1024 * 1024 * 1024)

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "[Error]: Device mounted path parameter missing.\n");
        exit(EXIT_FAILURE);
    }

    struct statvfs device;

    if (statvfs(argv[1], &device) == 0)
    {
        double total = (long double)device.f_blocks * device.f_frsize;
        double free = (long double)device.f_bfree * device.f_frsize;

        printf("Total Size: %.2f GB\n", (float)total / GB_FACTOR);
        printf("Free Space: %.2f GB\n", (float)free / GB_FACTOR);
        printf("Used: %.1f%%\n", (float)((100 * (total - free)) / total));
    }

    return 0;
}
