/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 08:55:23 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/11 18:16:58 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INPUT "Wrong or Incomplete Input \n"
# define USAGE0 "Usage:         (ONLY POSITIVE INTEGERS ALLOWED!)\n"
# define USAGE1 "./philo nbr_of_philos time_to_die time_to_eat time_to_sleep \
[nbr_of_times_each_philos_must_eat]\n"
# define EXMPL "For Example : ----> ./philo 5 80 100 300 [7]\n"
# define PHILO "Number of Philos should be at least 1 \n"
# define INIT_ERR "Failed to initiate \n"
# define TIME_STAMP "Timestampes must at least 60ms or above !\n"
# define MALLOC "Malloc failed\n"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "colors.h"

/* Stuctures */

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;
/*
** ./philo 5 600 500 300 [7]
*/

typedef enum s_mtx_code
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mtx_code;

typedef enum s_thread_code
{
	CREATE,
	JOIN,
	DETACH
}	t_thread_code;

typedef enum s_time_code
{
	MILISEC,
	MICROSEC,
}	t_time_code;

typedef enum s_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	TAKE_FORK,
}	t_philo_status;

typedef struct s_philo
{
	int			id;
	int			last_meal_time;//the time pqssed from last meal
	int			meals_counter;
	int			full;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;// each philo is a thread
	t_mtx		philo_mutex;// avoid races with monitor
	t_data		*data;
}	t_philo;

struct s_data
{
	int		philos_number;
	long	time_to_eat;
	long	time_to_die;
	long	time_to_sleep;
	int		nmr_limit_meals;// [7] | flag
	long	start_simulation;
	int		all_thread_ready;//thread synchnonisation
	int		end_simulation;//when a philo dies or all full
	t_mtx	data_mutex;//protection from races while rading from data
	t_mtx	msg_mutex;//protection when writing in message
	t_fork	*forks;//array of forks
	t_philo	*philos;//array of philo
};

/* Prototypes */

int		main(int ac, char **av);
int		parser(int ac, char **av);
int		init(char **av, t_data *data);
void	print_error(char *msg);

int		thread_handler(pthread_t *thread, void *(*thread_routine)(void *), void *data, t_thread_code num_thread);
int		mutex_handler(t_mtx *mutex, t_mtx_code num_mtx);
void    set_val(t_mtx *mutex, int *dest, int value);
int		get_val(t_mtx *mutex, int *value);
int		simulation_finished(t_data *data);
int		simulation(t_data *data);
void	wait_all_threads(t_data *data);
int		_usleep(t_data *data, int usec);
long	gettime(t_time_code time_code);
void	message_status(t_philo *philo, t_philo_status status);
void	*monitor_routine(void *arg);

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_isdigit(int c);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
int		ft_strcmp(char *s1, char *s2);

#endif
