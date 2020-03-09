#include <stdio.h>
#include "calc.h"

int main(int argc, char **argv)
{
    if(argc > 1)
        printf("%d\n", calc(argv[1]));
}