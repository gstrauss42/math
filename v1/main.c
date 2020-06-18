#include <stdio.h>
#include "calc.h"
#include <time.h>

int main(int argc, char **argv)
{
    int i = 0;
    while(i < 1000000)
    {
        printf("%d\n", calc(argv[1]));
        i++;
    }
    printf("%lu\n", clock());
}