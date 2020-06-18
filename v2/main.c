#include <stdio.h>
#include <time.h>

char        *calc_2(char *input);

int main(int argc, char **argv)
{
    int i = 0;
    while(i < 1000000)
    {
        printf("%s\n", calc_2(argv[1]));
        i++;
    }
    printf("%lu\n", clock());
}