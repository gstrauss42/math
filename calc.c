// at some point add exponant and root functionality and then perhaps algebra

#include "libft/libft.h"
#include "calc.h"
#include <stdio.h>

// a function to evaluate a mathematical string and return the interger answer
int     calc(char *math_str)
{
    if(sanitize(&math_str) == 1)
        return(0);
    printf("__cleaned string__\n%s\n\n__opperation procedures__\n", math_str);
    while(symbol_check(math_str) == 1)
    {
        opperation_order(&math_str);
        printf("                     step__:%s\n", math_str);
    }
    return(ft_atoi(math_str));
}

int     sanitize(char **math_str)
{
    int i = 0;
    int open = 0;
    int close = 0;
    *math_str = ft_strtrim(*math_str);
    while((*math_str)[i])
    {
        if((*math_str)[i] == '(')
            open++;
        if((*math_str)[i] == ')')
            close++;
        i++;
    }
    if(open != close)
        return(1);
    i = 0;
    while((*math_str)[i] && (((*math_str)[i] <= '9' && (*math_str)[i] >= '0') || (*math_str)[i] == '('\
        || (*math_str)[i] == ')' || (*math_str)[i] == ' ' || (*math_str)[i] == '\t' || (*math_str)[i] == '+'\
        || (*math_str)[i] == '-' || (*math_str)[i] == '*' || (*math_str)[i] == '/'))
        i++;
    if((*math_str)[i])
        return(1);
    i = 0;
    while((*math_str)[i])
    {
        if((*math_str)[i] == ' ' || (*math_str)[i] == '\t')
        {
            open = i;
            while((*math_str)[i + 1])
            {
                (*math_str)[i] = (*math_str)[i + 1];
                i++;
            }
            (*math_str)[i] = '\0';
            i = open;
        }
        else
            i++;
    }
    return(0);
}

// returns 0 if only numeric characters are found in array math_str else 1 if any non_numeric characters are found
int     symbol_check(char *math_str)
{
    int i = 0;
    while(math_str[i] >= '0' && math_str[i] <= '9')
        i++;
    if(math_str[i])
        return(1);
    else
        return(0);
}

// processes and returns the next opperation in the order of operations
void    opperation_order(char **math_str)
{
    if(bracket_check(*math_str))
    {
        printf("bracket calc\n");
        opperate(brac_location(*math_str), math_str);
    }
    else if(div_mult_check(*math_str))
    {
        printf("div_mult calc\n");
        opperate(div_mult_location(*math_str), math_str);
    }
    else if(add_sub_check(*math_str))
    {
        printf("add_sub calc\n");
        opperate(add_sub_location(*math_str), math_str);
    }
}

// the core maths calculations
void    opperate(int index, char **math_str)
{
    int i_index = index;
    char *re_assign = (char *)malloc(1024);
    int p = 0;
    int num1 = num_extract(*math_str, index);
    int num2;
    int i = index;
    while((*math_str)[i])
        i++;
    char *after_opp = (char *)malloc(i - index + 2);
    i = index;
    while((*math_str)[i] && (*math_str)[i] >= '0' && (*math_str)[i] <= '9')
        i++;
    while((*math_str)[i] && (((*math_str)[i] > 0 && (*math_str)[i] < '0') || ((*math_str)[i] > '9')))
        i++;
    num2 = num_extract(*math_str, i);
    while((*math_str)[index] && ((*math_str)[index] != '*' && (*math_str)[index] != '/' && (*math_str)[index] != '+' && (*math_str)[index] != '-'))
        index++;
    printf("i__:%d     %c\n", i, (*math_str)[i]);
    printf("i_index__: %d\n", i_index);
    printf("num1__:%d\n", num1);
    printf("num2__:%d\n", num2);
    printf("math_str__:%s\n", (*math_str));
    // addition calculation
    if((*math_str)[index] == '+')
    {
        printf("add_call\n");

        index = i_index;
        while((*math_str)[i] && ((*math_str)[i] >= '0' && (*math_str)[i] <= '9'))
            i++;
        while((*math_str)[i])
            after_opp[p++] = (*math_str)[i++];
        after_opp[p] = '\0';
        re_assign = ft_itoa(num1 + num2);
        printf("re_assign__:%s\n", re_assign);
        printf("after_opp__:%s\n", after_opp);
        p = 0;
        while(re_assign[p])
            (*math_str)[index++] = re_assign[p++];
        p = 0;
        while(after_opp[p])
            (*math_str)[index++] = after_opp[p++];
        (*math_str)[index] = '\0';
    }
    // subtraction calculation
    else if((*math_str)[index] == '-')
    {
        printf("sub_call\n");
        index = i_index;
        while((*math_str)[i] && ((*math_str)[i] >= '0' && (*math_str)[i] <= '9'))
            i++;
        while((*math_str)[i])
            after_opp[p++] = (*math_str)[i++];
        re_assign = ft_itoa(num1 - num2);
        p = 0;
        while(re_assign[p])
            (*math_str)[index++] = re_assign[p++];
        p = 0;
        while(after_opp[p])
            (*math_str)[index++] = after_opp[p++];
        (*math_str)[index] = '\0';
    }
    //multiplication calculation
    else if((*math_str)[index] == '*')
    {
        printf("mult_call\n");
        index = i_index;
        while((*math_str)[i] && ((*math_str)[i] >= '0' && (*math_str)[i] <= '9'))
            i++;
        while((*math_str)[i])
            after_opp[p++] = (*math_str)[i++];
        re_assign = ft_itoa(num1 * num2);
        p = 0;
        while(re_assign[p])
            (*math_str)[index++] = re_assign[p++];
        p = 0;
        while(after_opp[p])
            (*math_str)[index++] = after_opp[p++];
        (*math_str)[index] = '\0';
    }
    // division calculation
    else if((*math_str)[index] == '/')
    {
        printf("div_call\n");
        index = i_index;
        while((*math_str)[i] && ((*math_str)[i] >= '0' && (*math_str)[i] <= '9'))
            i++;
        while((*math_str)[i])
            after_opp[p++] = (*math_str)[i++];
        re_assign = ft_itoa(num1 / num2);
        p = 0;
        while(re_assign[p])
            (*math_str)[index++] = re_assign[p++];
        p = 0;
        while(after_opp[p])
            (*math_str)[index++] = after_opp[p++];
        (*math_str)[index] = '\0';
    }
}

int     num_extract(char *math_str, int index)
{
    char *str;
    int i = index;
    while(math_str[i] && math_str[i] >= '0' && math_str[i] <= '9')
        i++;
    str = (char *)malloc(i + 2);
    i = 0;
    while(math_str[index] && math_str[index] >= '0' && math_str[index] <= '9')
        str[i++] = math_str[index++];
    str[i] = '\0';
    return(ft_atoi(str));
}

// a function that returns the index of the first character in the mathematical opperation to process
int     brac_location(char *math_str)
{
    int hold;
    int check = 0;
    int index;
    int i = 0;
    while(math_str[i])
    {
        hold = check;
        if(math_str[i] == '(')
            check++;
        if(math_str[i] == ')')
            check--;
        if(check > hold)
            index = i;
        i++;
    }
    return(index + 1);
}

// a function that returns the index of the first character in the mathematical opperation to process
int     div_mult_location(char *math_str)
{
    int i = 0;
    while(math_str[i])
    {
        if (math_str[i] == '*' || math_str[i] == '/')
        {
            i--;
            break;
        }
        i++;
    }
    while(math_str[i - 1] == ' ' || math_str[i - 1] == '\t')
        i--;
    while(i > 0 && math_str[i - 1] >= '0' && math_str[i - 1] <= '9')
    {
        i--;
    }
    
    return(i);
}

// a function that returns the index of the first character in the mathematical opperation to process
int     add_sub_location(char *math_str)
{
    int i = 0;
    while(math_str[i] && (math_str[i] != '+' && math_str[i] != '-'))
        i++;
    i--;
    while(math_str[i - 1] == ' ' || math_str[i - 1] == '\t')
        i--;
    while(i > 0 && math_str[i - 1] >= '0' && math_str[i - 1] <= '9')
        i--;
    return(i);
}

// a function that returns 1 if array math_str contains any multiplication or division characters else 0
int     div_mult_check(char *math_str)
{
    int i = 0;
    while(math_str[i])
    {
        if(math_str[i] == '/' || math_str[i] == '*')
            return(1);
        i++;
    }
    return(0);
}

// a function that returns 1 if array math_str contains any addition or subtraction characters else 0
int     add_sub_check(char *math_str)
{
    int i = 0;
    while(math_str[i])
    {
        if(math_str[i] == '+' || math_str[i] == '-')
            return(1);
        i++;
    }
    return(0);
}

// a function that checks if array math_str contains any brackets
int     bracket_check(char *math_str)
{
    int i = 0;
    while(math_str[i])
    {
        if(math_str[i] == '(' || math_str[i] == ')')
        {
            return(1);
        }
        i++;
    }
    return(0);
}

// converts ascii characters into intergers
int		ft_atoi(const char *str)
{
	int		res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'\
			|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] > '9' || str[i] < '0')
			return (res * sign);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}

// interger to ascii converter
static int		size(int n)
{
	long	i;
	int		q;

	q = 0;
	i = 1;
	if (n == 2147483647)
		n--;
	while (n / i != 0)
	{
		i = i * 10;
		q++;
	}
	return (q);
}

static char		*neg(int n)
{
	int		i;
	char	*ret;
	int		c;

	c = 100000000;
	i = 0;
	ret = (char *)malloc(12 * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	ret[i] = '-';
	i++;
	n = ((n + 8) / 10) * -1;
	while (n > 0)
	{
		ret[i] = n / c + 48;
		i++;
		n = n - ((n / c) * c);
		c = c / 10;
	}
	ret[i] = '8';
	ret[i + 1] = '\0';
	return (ret);
}

static char		*test(char *ret)
{
	ret[0] = '0';
	ret[1] = '\0';
	return (ret);
}

char			*ft_itoa(int n)
{
	char	*ret;
	int		q;

	q = size(n);
	if (n == -2147483648)
		return (neg(n));
	ret = (char *)malloc(size(n) + 1 * sizeof(char *));
	if (!ret)
		return (NULL);
	if (n < 0 && n > -2147483648)
	{
		ret[0] = '-';
		n = n * -1;
		q++;
	}
	ret[q] = '\0';
	if (n == 0)
		return (test(ret));
	while (n != 0 && q-- >= 0)
	{
		ret[q] = n % 10 + '0';
		n = n / 10;
	}
	return (ret);
}