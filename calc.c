// at some point add exponant and root functionality and then perhaps algebra
// write brac location

#include "calc.h"

// a function to evaluate a mathematical string and return the interger answer
int     calc(char *math_str)
{
    while(symbol_check(math_str))
        opperation_order(&math_str);
    return(ft_atoi(math_str));
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
        opperate(brac_location(*math_str), math_str);
    else if(div_mult_check(*math_str))
        opperate(div_mult_location(*math_str), math_str);
    else if(add_sub_check(*math_str))
        opperate(add_sub_location(*math_str), math_str);
}

// make it work with memory adresses all math_str indexes are currently working as if its a 1D array
// the core maths calculations
void    opperate(int index, char **math_str)
{
    char *re_assign = (char *)malloc(1024);
    int p = 0;
    int num1 = num_extract(*math_str, index);
    int num2;
    int i = index;
    while((*math_str)[i])
        i++;
    char *after_opp = (char *)malloc(i - index + 1);
    i = index;
    while((*math_str)[i] && (*math_str)[i] >= '0' && (*math_str)[i] <= '9')
        i++;
    while((*math_str)[i] && (*math_str)[i] >= '9' && (*math_str)[i] <= '0')
        i++;
    num2 = num_extract(*math_str, i);
    while((*math_str)[index] != '*' || (*math_str)[index] != '/' || (*math_str)[index] != '+' || (*math_str)[index] != '-')
        index++;
    // addition calculation
    if((*math_str)[index] == '+')
    {
        while((*math_str)[i])
            after_opp[p++] = (*math_str)[i++];
        re_assign = ft_itoa(num1 + num2);
        p = 0;
        while(re_assign[p])
            (*math_str)[index++] = re_assign[p++];
        p = 0;
        while(after_opp[p])
            (*math_str)[index++] = after_opp[p++];
        (*math_str[index]) = '\0';
    }
    // minus calculation
    else if((*math_str)[index] == '-')
    {
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
    while(math_str[i + 1] && math_str[i] >= '0' && math_str[i] <= '9')
        i++;
    str = (char *)malloc(i + 1);
    i = 0;
    while(math_str[index + 1] && math_str[index] >= '0' && math_str[index] <= '9')
        str[i++] = math_str[index];
    str[i] = '\0';
    return(ft_atoi(str));
}

// a function that returns the index of the first character in the mathematical opperation to process
int     brac_location(char *math_str)
{
    int i = 0;
    while(math_str[i])
    {
        // find correct brac location
        //if(math_str[i] == '(' || math_str[i] == ')')
        //    return(i)
        i++;
    }
    return(0);
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
    while(math_str[i] != '+' || math_str[i] != '-')
    {
        i++;
    }
    i--;
    while(math_str[i - 1] == ' ' || math_str[i - 1] == '\t')
        i--;
    while(i > 0 && math_str[i - 1] >= '0' && math_str[i - 1] <= '9')
    {
        i--;
    }
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