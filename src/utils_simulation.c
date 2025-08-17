/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:25:20 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/17 13:59:42 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	mutex_handler(t_mtx *mutex, t_mtx_code mtx_code)
{
	int	ret;

	ret = 0;
	if (mtx_code == INIT)
		ret = pthread_mutex_init(mutex, NULL);
	else if (mtx_code == LOCK)
		ret = pthread_mutex_lock(mutex);
	else if (mtx_code == UNLOCK)
		ret = pthread_mutex_unlock(mutex);
	else if (mtx_code == DESTROY)
		ret = pthread_mutex_destroy(mutex);
	return (ret);
}

int	thread_handler(pthread_t *thread, void *(*thread_routine)(void *), void *data, t_thread_code thread_code)
{
	int	ret;

	ret = 0;
	if (thread_code == CREATE)
		ret = pthread_create(thread, NULL, thread_routine, data);
	else if (thread_code == JOIN)
		ret = pthread_join(*thread, NULL);
	else if (thread_code == DETACH)
		ret = pthread_detach(*thread);
	return (ret);
}
