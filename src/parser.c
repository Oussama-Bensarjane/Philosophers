/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 08:55:16 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/09 12:33:06 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_usage(char *arg)
{
	char	*ptr;
	int		len;

	ptr = arg;
	while (*ptr == '0' || *ptr == '+')
		ptr++;
	len = ft_strlen(ptr);
	if (len > 10 || (len == 10 && ft_strcmp(ptr, "2147483647") > 0))
		return (print_error(RED INPUT RST \
			GREEN USAGE0 RST USAGE1 YELLOW EXMPL RST), 1);
	while (*ptr)
	{
		if (!ft_isdigit(*ptr))
			return (print_error(RED INPUT RST GREEN USAGE0 \
				RST USAGE1 YELLOW EXMPL RST), 1);
		ptr++;
	}
	return (0);
}

int	parser(int ac, char **av)
{
	int	i;

	if ((ac != 5 && ac != 6))
		return (print_error(RED INPUT RST GREEN USAGE0 \
			RST USAGE1 YELLOW EXMPL RST), 1);
	i = 1;
	while (i < ac && av[i])
	{
		if (ft_atoi(av[1]) == 0)
			return (print_error(RED PHILO RST USAGE1 \
				YELLOW EXMPL RST), 1);
		if (check_usage(av[i++]))
			return (1);
	}
	return (0);
}
