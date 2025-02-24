#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 256

// create a PPM image with a gradient from black to white
int main(void)
{
    // open file
    int fd = open("../output/first.ppm", O_CREAT | O_WRONLY, 0644);
    if(fd < 0)
    {
        perror("open");
        return EXIT_FAILURE;
    }

    // header
    dprintf(fd, "P3\n%d %d\n%d\n", SIZE, SIZE, SIZE - 1);

    // body
    for (int i = 0; i < SIZE; ++i)
    {
        printf("Lines remain: %d\n", SIZE - i);
        for (int j = 0; j < SIZE; ++j)
            dprintf(fd, "%d %d %d\n", j, i, 0);
    }
    printf("Done.\n");

    // close file
    close(fd);
    return EXIT_SUCCESS;
}
