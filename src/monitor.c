/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:07:06 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/17 14:07:07 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static	int philo_die(t_philo *philo)
{
	long	last_meal;
	long	now;
	long	time_to_die;

	if (get_val(&philo->philo_mutex, &philo->full))
		return (0);
	time_to_die = philo->data->time_to_die / 1000;// convert usec → ms cz in init i converted all to micro for usleep !
	last_meal = get_val(&philo->philo_mutex, &philo->last_meal_time);
	now = gettime(MILISEC);
	if ((now - last_meal) > time_to_die)
		return (1);
	return (0);
}

void *monitor_routine(void *arg)
{
	t_data *data;
	int i;

	data = (t_data *)arg;
	/*
	 * make sure all threads or philo are runnig
	 * 		before starting the monitor (spin lock till all philos ran)
	*/
	while (!all_philo_running(&data->data_mutex, &data->philos_running_nbr, data->philos_number))
		usleep(100);
	while (!simulation_finished(data))
	{
		i = -1;
		while (++i < data->philos_number && !simulation_finished(data))
		{
			if (philo_die(data->philos + i))
			{
				message_status(&data->philos[i], DIED);
				set_val(&data->data_mutex, &data->end_simulation, 1);
				return (NULL);
			}
		}
		if (get_val(&data->philos->philo_mutex, &data->philos->full))
			set_val(&data->philos->philo_mutex, &data->philos->data->end_simulation, 1);
		usleep(400);
	}
	return (NULL);
}

