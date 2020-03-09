// at some point add exponant and root functionality and then perhaps algebra

int		ft_atoi(const char *str);
int     symbol_check(char *math_str);
void    opperation_order(char **math_str);
int     bracket_check(char *math_str);
int     div_mult_check(char *math_str);
int     add_sub_check(char *math_str);

// a function to evaluate a mathematical string and return the interger answer
int     math(char *math_str)
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

// finish this function
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
    int first_sapce = 1;
    while(math_str[i])
    {
        if (math_str[i] == '*' || math_str[i] == '/')
            break;
        i++;
    }
    while(math_str[i - 1] == ' ' || math_str[i - 1] == '\t')
        i--;
    while(i > 0 && num_check(math_str))
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