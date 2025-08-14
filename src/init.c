/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:55:15 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/11 18:04:52 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_number;
	int	left_id;
	int	right_id;

	philo_number = philo->data->philos_number;
	left_id = philo_pos;
	right_id = (philo_pos + 1) % philo_number;
	if (left_id < right_id)
	{
		philo->first_fork = &forks[left_id];
		philo->second_fork = &forks[right_id];
	}
	else
	{
		philo->first_fork = &forks[right_id];
		philo->second_fork = &forks[left_id];
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

static int set_ups(t_data *data)
{
	int	i;
	t_philo *philo;

	data->end_simulation = 0;
	data->all_thread_ready = 0;
	data->philos = safe_malloc(sizeof(t_philo) * data->philos_number);
	data->forks = safe_malloc(sizeof(t_fork) * data->philos_number);
	if (!data->forks || !data->philos)
		return (1);
	mutex_handler(&data->data_mutex, INIT);
	i = -1;
	while (++i < data->philos_number)
	{
		if (mutex_handler(&data->forks[i].fork, INIT))
			return (data->forks[i].fork_id = i, 1);
		data->forks[i].fork_id = i;
	}
	i = -1;
	while (++i < data->philos_number)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meals_counter = 0;
		philo->data = data;
		mutex_handler(&philo->philo_mutex, INIT);
		assign_forks(philo, data->forks, i);
	}
	return (0);
}

int	init(char **av, t_data *data)
{
	data->philos_number = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]) * 1000;
	data->time_to_eat = ft_atoi(av[3]) * 1000;
	data->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (data->time_to_die < 60000 || data->time_to_eat < 60000 || data->time_to_sleep < 60000)
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
