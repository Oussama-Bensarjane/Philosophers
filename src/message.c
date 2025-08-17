/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:22:06 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/17 12:44:07 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * [timestamp] [philo id] [message]
 * 
 * thread safe --> t_mtx msg_mutex , message mutex
 */

void	message_status(t_philo *philo, t_philo_status status)
{
	long	passed_time;

	mutex_handler(&philo->data->msg_mutex, LOCK);
	if (philo->full)
	{
		mutex_handler(&philo->data->msg_mutex, UNLOCK);
		return ;
	}
	passed_time = gettime(MILISEC) - philo->data->start_simulation;
	if (status == TAKE_FORK && !simulation_finished(philo->data))
		printf("%-4ld %ld has taken a fork\n", passed_time, philo->id + 1);
	else if (status == EATING && !simulation_finished(philo->data))
		printf("%-4ld %ld is eating\n", passed_time, philo->id + 1);
	else if (status == SLEEPING && !simulation_finished(philo->data))
		printf("%-4ld %ld is sleeping\n", passed_time, philo->id + 1);
	else if (status == THINKING && !simulation_finished(philo->data))
		printf("%-4ld %ld is thinking\n", passed_time, philo->id + 1);
	else if (status == DIED)
		printf("%-4ld %ld died\n", --passed_time, philo->id + 1);
	else if (status == DIED1)
		printf("%-4ld %ld died\n", passed_time, philo->id + 1);
	mutex_handler(&philo->data->msg_mutex, UNLOCK);
}
