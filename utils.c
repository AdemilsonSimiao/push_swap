int ft_isspace(int c)
{
	if (c > 32 && c < 127)
		return (1);
	return (0);
}

int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}