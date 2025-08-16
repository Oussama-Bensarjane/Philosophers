/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:25:20 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/11 13:31:29 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 * Spinlock Thread
 * 		where a thread repeatedly checks if a resource is available, 
 * 			rather than going to sleep, until it becomes available
*/
void	wait_all_threads(t_data *data)
{
	while (!(get_val(&data->data_mutex, &data->all_thread_ready)))
		;
}

/**
 * monitor busy waitttt untill all philo are running
 */
int	all_philo_running(t_mtx *mutex, long *philos, long philo_nbr)
{
	int	ret;

	ret = 0;
	mutex_handler(mutex, LOCK);
	if (*philos == philo_nbr)
		ret = 1;
	mutex_handler(mutex, UNLOCK);
	return (ret);
}
/**
 * increment running philo to synch with the monitor
 */
void	increment_synch_var(t_mtx *mutex, long *value)
{
	mutex_handler(mutex, LOCK);
	(*value)++;
	mutex_handler(mutex, UNLOCK);
}
