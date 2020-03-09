int     bracket_check(char *math_str);
int     symbol_check(char *math_str);
int     math(char *math_str);
#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc > 1)
        printf("%d\n", math(argv[1]));
}