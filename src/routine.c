/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:00:47 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/17 14:01:32 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * 		eat task
 * 1) grap the fork
 * 2) eat : write eat msg, update last meal, update meals counter
 * 3) release the forks
 */

static void	eat(t_philo *philo)
{
	mutex_handler(&philo->first_fork->fork, LOCK);
	message_status(philo, TAKE_FORK);
	mutex_handler(&philo->second_fork->fork, LOCK);
	message_status(philo, TAKE_FORK);

	set_val(&philo->philo_mutex, &philo->last_meal_time , gettime(MILISEC));
	philo->meals_counter++;
	message_status(philo, EATING);
	_usleep(philo->data, philo->data->time_to_eat);
	if (philo->data->nmr_limit_meals > 0 && \
		get_val(&philo->philo_mutex, &philo->meals_counter) == philo->data->nmr_limit_meals)
		set_val(&philo->philo_mutex, &philo->full, 1);
	mutex_handler(&philo->first_fork->fork, UNLOCK);
	mutex_handler(&philo->second_fork->fork, UNLOCK);
}

/**
 *  Thinking
 */

static void	thinking(t_philo *philo)
{
	message_status(philo, THINKING);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// SpinLock
	wait_all_threads(philo->data);
	// set last meal time
	set_val(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISEC));
	// increment the a var in data to synch with the monitor with each philo
	increment_synch_var(&philo->data->data_mutex, &philo->data->philos_running_nbr);
	while (!simulation_finished(philo->data))
	{
		if (get_val(&philo->philo_mutex, &philo->full))//TODO thread handle
			break ;
		// eat
		eat(philo);
		// sleep
		message_status(philo, SLEEPING);
		_usleep(philo->data, philo->data->time_to_sleep);
		// Think
		thinking(philo);
	}
	return (NULL);
}
