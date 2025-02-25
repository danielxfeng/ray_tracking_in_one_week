#include "../supp/vec3.h"
#include "../supp/color.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 256

int main(void)
{
    // open file
    int fd = open("../output/second.ppm", O_CREAT | O_WRONLY, 0644);
    if (fd < 0)
    {
        perror("open");
        return EXIT_FAILURE;
    }

    // header
    dprintf(fd, "P3\n%d %d\n%d\n", SIZE, SIZE, SIZE - 1);

    // body
    for (int i = 0; i < SIZE; ++i)
    {
        printf("Lines remian: %d\n", SIZE - i);
        for (int j = 0; j < SIZE; ++j)
        {
            t_color pixel_color = vec3_new((float)j / (SIZE - 1), (float)i / (SIZE - 1), 0.0);
            write_color(fd, pixel_color);
        }
    }
    printf("Done!\n");

    // close file
    close(fd);
    return(EXIT_SUCCESS);
}
