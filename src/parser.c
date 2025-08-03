#include "../include/philo.h"

static int	check_usage(char *arg)
{
	char	*ptr;
	int		len;

	ptr = arg;
	len = ft_strlen(ptr);
	while (*ptr)
	{
		while (*ptr == '0')
			ptr++;
		if (!ft_isdigit(*ptr) || len > 10)
		{
			printf("len-->[%d]\n", len);
			printf("arg-->[%s]\n", arg);
			return (print_error_usage(USAGE, 2), 1);
		}
		if (ptr + 1)
			ptr++;
	}
	return (0);
}
//2147483647
int	parser(int ac, char **av)
{
	int i;

	if (ac != 5 && ac != 6)
		return (print_error_usage(USAGE, 2), 1);
	i = 1;
	while (i < ac && av[i])
	{
		if (check_usage(av[i++]))
			return (1);
	}
	return (0);
}