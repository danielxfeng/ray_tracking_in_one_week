#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

# define SIZE 256

int main(void)
{
    int fd = open("../output/first.ppm", 1);
    printf("P3\n\n%d\n", SIZE);
    
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            double r = j / (SIZE - 1) * SIZE;
            double g = i / (SIZE - 1) * SIZE;
            double b = 0.0;
        }
    }


}
