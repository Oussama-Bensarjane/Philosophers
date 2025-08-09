/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:55:15 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/09 18:48:40 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*safe_malloc(int bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		return (print_error(RED MALLOC RST), 1);
	return (ret);
}

static int set_ups(t_data *data)
{
	int	i;

	data->end_simulation = 0;
	data->philos = safe_malloc(sizeof(t_philo) * data->philos_number);
	data->fork = safe_malloc(sizeof(t_fork) * data->philos_number);
	i = 0;
	while (i < data->philos_number)
	{
		mutex_handler(&data->fork[i].fork, INIT);
		data->fork[i].fork_id = i++;
	}
		
}

int	init(char **av, t_data *data)
{
	data->philos_number = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]) * 1e3;
	data->time_to_eat = ft_atoi(av[3]) * 1e3;
	data->time_to_sleep = ft_atoi(av[4]) * 1e3;
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4 || data->time_to_sleep < 6e4)
		return (print_error(RED INIT_ERR RST YELLOW TIME_STAMP RST USAGE1), 1);
	if (av[5])
		data->nmr_limit_meals = ft_atoi(av[5]);
	else
		data->nmr_limit_meals = -1;
	data->start_simulation = 0;
	if (set_up(&data))
		return (1);
	return (0);
}
