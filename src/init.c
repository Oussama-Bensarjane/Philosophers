/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:55:15 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/17 09:55:47 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks)
{
	int philo_nbr;

	philo_nbr = philo->data->philos_number;
	philo->first_fork = &forks[(philo->id + 1) % philo_nbr];
	philo->second_fork = &forks[philo->id];
	if (philo->id % 2)
	{
		philo->first_fork = &forks[philo->id];
		philo->second_fork = &forks[(philo->id + 1) % philo_nbr];
	}
}
static void	*safe_malloc(int bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
	{
		print_error(RED MALLOC RST);
		return (NULL);
	}
	return (ret);
}

static int	init_philos(t_data *data)
{
	t_philo *philo;
	int		i;

	i = -1;
	while (++i < data->philos_number)
	{
		philo = data->philos + i;
		philo->id = i;
		philo->full = 0;
		philo->meals_counter = 0;
		philo->thread_id = 0;
		philo->data = data;
		if (mutex_handler(&philo->philo_mutex, INIT))
			return (1);
		assign_forks(philo, data->forks);
	}
	return (0);
}

static int set_ups(t_data *data)
{
	int		i;

	data->end_simulation = 0;
	data->all_thread_ready = 0;
	data->philos_running_nbr = 0;
	data->philos = safe_malloc(sizeof(t_philo) * data->philos_number);
	data->forks = safe_malloc(sizeof(t_fork) * data->philos_number);
	if (!data->forks || !data->philos)
		return (1);
	i = -1;
	while (++i < data->philos_number)
		data->forks[i].initialized = 0;
	i = -1;
	while (++i < data->philos_number)
	{
		if (mutex_handler(&data->forks[i].fork, INIT))
			return (data->forks[i].fork_id = i, 1);
		data->forks[i].fork_id = i;
		data->forks[i].initialized = 1;
	}
	if (init_philos(data))
		return (1);
	return (0);
}

int	init(char **av, t_data *data)
{
	data->philos_number = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]) * 1000;
	data->time_to_eat = ft_atoi(av[3]) * 1000;
	data->time_to_sleep = ft_atoi(av[4]) * 1000;
	data->philos = NULL;
	data->forks = NULL;
	if (mutex_handler(&data->data_mutex, INIT))
		return (1);
	if (mutex_handler(&data->msg_mutex, INIT))
		return (1);
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
		return (print_error(RED INIT_ERR RST YELLOW TIME_STAMP RST USAGE1), 1);
	if (av[5])
		data->nmr_limit_meals = ft_atoi(av[5]);
	else
		data->nmr_limit_meals = -1;
	data->start_simulation = 0;
	if (set_ups(data))
		return (1);
	return (0);
}
