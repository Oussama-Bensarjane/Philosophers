/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:58:49 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/17 13:59:52 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	_usleep(t_data *data, int usec)
{
	long	start;

	start = gettime(MICROSEC);
	if (start == -1)
		return (1);
	while ((gettime(MICROSEC) - start) < usec)
	{
		if (simulation_finished(data))
			break ;
		usleep(50);// sleep in very small chunks (0.5 ms)
	}
	return (0);
}

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	if (time_code == MILISEC)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSEC)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	return (-1);
}

/*
 * Spinlock Thread
 * 		where a thread repeatedly checks if a resource is available, 
 * 			rather than going to sleep, until it becomes available
*/

void	wait_all_threads(t_data *data)
{
	while (!(get_val(&data->data_mutex, &data->all_thread_ready)))
		usleep(50);
}
