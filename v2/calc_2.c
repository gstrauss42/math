// calc_2
// adding your own operations is easy, simply update the inclusion list in char_check(), add the function to perform_calculation() and add the symbol to the symbols[] variable in opperate in the order you want it performed in

// main for testing
char        *brack_chop(char *input, int start);
char        *clean(char *input);
char        *calc_2(char *input);
char        *calculate(char *input);
char        *perform_calculation(char *input, int counter);
char        *reassign(char *input, int counter, int number);
_Bool       bad_char(char **input);
_Bool       char_check(char character);
_Bool       solved_check(char *input, int start);
int         first_val(char *input, int counter);
int         second_val(char *input, int counter);
int         exponent(int num, int exponent);
int         ft_atoi(const char* str);
int         bracket_locate(char *input);
int         simple_calc(int num1, int num2, char sign);

char        *calc_2(char *input)//calculator function
{
    char *output = 0;

    input   = clean(input);
    output  = calculate(input);
    return(output);
}

// list of all suported characters
_Bool        char_check(char character)
{
    if(character == '+')
        return(1);
    else if(character == '-')
        return(1);
    else if(character == '*')
        return(1);
    else if(character == '/')
        return(1);
    else if(character >= '0' && character <= '9')
        return(1);
    else if(character == '(')
        return(1);
    else if(character == '^')
        return(1);
    else if(character == ')')
        return(1);
    return(0);    
}

int         simple_calc(int num1, int num2, char sign)
{
    int ret;
    if(sign == '+')
        ret = num1 + num2;
    else if(sign == '-')
        ret = num1 - num2;
    else if(sign == '*')
        ret = num1 * num2;
    else if(sign == '/')
        ret = num1 / num2;
    else if(sign == '^')
        ret = exponent(num1, num2);
    return(ret);
}

// just need to write the maths functions now
char        *perform_calculation(char *input, int counter)
{
    int num1 = first_val(input, counter);
    int num2 = second_val(input, counter);
    input = reassign(input, counter, simple_calc(num1, num2, input[counter]));
    return(input);
}

//find correct brackets and set counter to open of those brackets else 0 then left to right bodmas up till end or close bracket
char        *opperate(char *input)
{
    char symbols[7] = {'^', '*', '/', '+', '-'};
    int counter = 0, start = 0, sym_counter = 0;
    //determines if the string contains brackets
    while(input[counter] && input[counter] != ')' && input[counter] != '(')
        counter++;
    if(!input[counter])
        counter = 0;
    else
        counter = bracket_locate(input);
    start = counter;
    //core segemented calculator
    while(symbols[sym_counter])
    {
        while(input[counter] != ')' && input[counter])
        {
            if(input[counter] == symbols[sym_counter])
            {
                input = perform_calculation(input, counter);
                sym_counter = 0;
                counter = start;
            }
            counter++;
        }
        counter = start;
        sym_counter++;
    }
    if(start != 0 || input[0] == '(')
        input = brack_chop(input, start);
    return(input);
}

char        *brack_chop(char *input, int start)
{
    while(input[start + 1] != ')')
    {
        input[start] = input[start + 1];
        start++;
    }
    while(input[start + 1] && input[start + 2])
    {
        input[start] = input[start + 2];
        start++;
    }
    input[start] = '\0';
    return(input);
}

char        *clean(char *input)//recursivley calls itself until the string is clean
{
    if(bad_char(&input))
        clean(input);
    return(input);
}

_Bool       unsolved(char *input)//check to see if more math needs to be done
{
    int counter = 0;
    if(input[counter] == '-')
        counter++;
    while(input[counter] && input[counter] >= '0' && input[counter] <= '9')
        counter++;
    if(input[counter] >= 3)
        return(1);
    else
        return(0);
}

int         bracket_locate(char *input) //locates and returns the index of the opening bracket of the most nested set of brackets
{
    int position = 0, counter = 0, bracket = 0, bracket_compare = 0;
    while(input[counter])
    {   
        if(input[counter] == '(')
            bracket++;
        else if(input[counter] == ')')
            bracket--;
        if(bracket > bracket_compare)
        {
            position = counter;
            bracket_compare = bracket;
        }
        counter++;
    }
    return(position);
}

_Bool       solved_check(char *input, int start) //determines if the segment is fully calculated
{
    start++;
    if(input[start] == '-')
        start++;
    while(input[start] && input[start] != ')')
    {
        if(input[start] >= '0' && input[start] <= '9')
            start++;
        else
            return(0);
    }
    return(1);
}

char        *calculate(char *input) //solves the expression
{
    while(unsolved(input) == 1)
        input = opperate(input);
    return(input);
}

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

_Bool       bad_char(char **input)//finds the next unsupported character and removes it
{
    int counter = 0;
    while((*input)[counter] && char_check((*input)[counter]))
        counter++;
    if((*input)[counter])
    {
        while((*input)[counter + 1])
        {
            (*input)[counter] = (*input)[counter + 1];
            counter++;
        }
        (*input)[counter] = '\0';
        return(1);
    }
    return(0);
}

char        *reassign(char *input, int counter, int number)
{
    int start = counter, end = counter, mem = 1;
    while(start > 0 && input[start - 1] >= '0' && input[start - 1] <= '9')
        start--;
    while(input[end + 1] && input[end + 1] >= '0' && input[end + 1] <= '9')
        end++;
    counter = end;
    while(input[end])
    {
        end++;
        mem++;
    }
    char holder[mem];
    mem = 0;
    end = counter;
    counter++;
    while(input[counter])
        holder[mem++] = input[counter++];
    //implementation of itoa
    if(number < 0)
    {
        input[start++] = '-';
        number = number * -1;
    }
    if(number == 0)
    {
        input[start++] = '0';
    }
    else
    {
        int temp = number;
        int div = 1;
        while(temp > div * 10)
            div = div * 10;
        while(div >= 1)
        {
            input[start++] = temp / div + '0';
            temp = temp - ((temp / div) * div);
            div = div / 10;
        }
        if(temp != 0)
            input[start++] = temp + '0'; 
    }
    mem = 0;
    while(holder[mem])
        input[start++] = holder[mem++];
    input[start] = '\0';
    return(input);
}

int         first_val(char *input, int counter)
{
    int counter1 = 0, size = counter;
    while(input[counter - 1] >= '0' && input[counter - 1] <= '9')
        counter--;
    char buff[size - counter + 1];
    while(counter != size)
        buff[counter1++] = input[counter++];    
    buff[counter1] = '\0';
    return(ft_atoi(buff));
}

int         second_val(char *input, int counter)
{
    int counter1 = 0, size = counter;
    while(input[counter + 1] >= '0' && input[counter + 1] <= '9')
        counter++;
    char buff[(counter - size) + 1];
    size++;
    while(size <= counter)
        buff[counter1++] = input[size++];    
    buff[counter1] = '\0';
    return(ft_atoi(buff));
}

int         exponent(int num, int exponent)
{
    int holder = num;
    while(exponent < 1)
    {
        num = num * holder;
        exponent--;
    }
    return(num);
}