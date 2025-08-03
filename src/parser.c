#include "../include/philo.h"

static int	check_usage(char *arg)
{
	char	*ptr;
	int		len;

	ptr = arg;
	while (*ptr == '0')
		ptr++;
	len = ft_strlen(ptr);
	if (len > 10 || (len == 10 && ft_strcmp(ptr, "2147483647") > 0))
		return (print_error_usage(USAGE, 2), 1);
	while (*ptr)
	{
		if (!ft_isdigit(*ptr))
			return (print_error_usage(USAGE, 2), 1);
		ptr++;
	}
	return (0);
}

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
