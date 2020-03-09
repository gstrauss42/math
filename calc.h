#ifndef CALC_H
# define CALC_H

#include <stdlib.h>

int		ft_atoi(const char *str);
int     symbol_check(char *math_str);
void    opperation_order(char **math_str);
int     bracket_check(char *math_str);
int     div_mult_check(char *math_str);
int     add_sub_check(char *math_str);
int     brac_location(char *math_str);
int     div_mult_location(char *math_str);
int     add_sub_location(char *math_str);
char    *ft_itoa(int n);
void    opperate(int index, char **math_str);
int     num_extract(char *math_str, int index);
int     calc(char *math_str);
int     sanitize(char *math_str);

#endif