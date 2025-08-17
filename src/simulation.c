/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:05:36 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/17 14:08:22 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 * ./philo 5 80 90 100 [5]
 * 0) if no meat --> return , [0]
 * 0,1) if only 1 philo, custom function ad hoc
 * 1) Create all threads, all philos
 * 2) Create Monitor Thread --> looking for any dead 
 * 3) Synchronisation the beginning of the simulation
 *      cz: pthread_creat --> the philo start runni!!
 *      should every philo start simultaneously
 * 4) Joinin ALL
*/

static void *one_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
    wait_all_threads(philo->data);
    message_status(philo, TAKE_FORK);
	_usleep(philo->data, philo->data->time_to_die);
    message_status(philo, DIED1);
	return (NULL);
}

static int one_philo_case(t_data *data)
{
    thread_handler(&data->philos[0].thread_id, one_philo_routine, &data->philos[0], CREATE);
    data->start_simulation = gettime(MILISEC);
    set_val(&data->data_mutex, &data->all_thread_ready, 1);
    thread_handler(&data->philos[0].thread_id, NULL, NULL, JOIN);
    return 0;
}

int	simulation(t_data *data)
{
	int i;

	if (data->nmr_limit_meals == 0)
		return (0);// return and clean
	if (data->philos_number == 1)
		return (one_philo_case(data));
	else
	{
		i = -1;
		while (++i < data->philos_number)
			thread_handler(&data->philos[i].thread_id, thread_routine, &data->philos[i], CREATE);
	}
	if (thread_handler(&data->monitor, monitor_routine, data, CREATE))
    	return (1);
	// Start of the simulation
	data->start_simulation = gettime(MILISEC);
	// 1) Now all threads are ready!
	set_val(&data->data_mutex, &data->all_thread_ready, 1);

	i = -1;
	while (++i < data->philos_number)
		thread_handler(&data->philos[i].thread_id, NULL, NULL, JOIN);
	thread_handler(&data->monitor, NULL, NULL, JOIN);
	return (0);
}
