/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:05:36 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/11 18:29:46 by obensarj         ###   ########.fr       */
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
	if (philo->data->nmr_limit_meals > 0 && philo->meals_counter == philo->data->nmr_limit_meals)
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
void	*thread_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// SpinLock
	
	wait_all_threads(philo->data);
	
	//set last meal time
	while (!simulation_finished(philo->data))
	{
		if (philo->full)//TODO thread handle
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

/*
 * ./philo 5 80 90 100 [5]
 * 0) if no meat --> return , [0]
 * 0,1) if only 1 philo, custom function
 * 1) Create all threads, all philos
 * 2) Create Monitor Thread --> looking for any dead 
 * 3) Synchronisation the beginning of the simulation
 *      cz: pthread_creat --> the philo start runni!!
 *      should every philo start simultaneously
 * 4) Joinin ALL
*/

void *one_philo_routine(void *arg)
{
    t_philo *p = arg;
    // wait_all_threads(p->data);
    message_status(p, TAKE_FORK);
    _usleep(p->data, p->data->time_to_die); // can’t eat; will “die”
    return NULL;
}

int one_philo_case(t_data *data)
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
	else if (data->philos_number == 1)
		return (one_philo_case(data));
	else
	{

		i = -1;
		while (++i < data->philos_number)
			thread_handler(&data->philos[i].thread_id, thread_routine, &data->philos[i], CREATE);
	
	}
	// Start of the simulation
	data->start_simulation = gettime(MILISEC);
	// 1) Now all threads are ready!
	set_val(&data->data_mutex, &data->all_thread_ready, 1);

	i = -1;
	while (++i < data->philos_number)
		thread_handler(&data->philos[i].thread_id, NULL, NULL, JOIN);
	return (0);
}
