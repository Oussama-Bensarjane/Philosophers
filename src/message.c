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
		printf("%-4ld %ld has taken a fork\n", passed_time, philo->id);
	else if (status == EATING && !simulation_finished(philo->data))
		printf("%-4ld %ld is eating\n", passed_time, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->data))
		printf("%-4ld %ld is sleeping\n", passed_time, philo->id);
	else if (status == THINKING && !simulation_finished(philo->data))
		printf("%-4ld %ld is thinking\n", passed_time, philo->id);
	else if (status == DIED)
		printf("%-4ld %ld died\n", passed_time, philo->id);
	mutex_handler(&philo->data->msg_mutex, UNLOCK);
}
