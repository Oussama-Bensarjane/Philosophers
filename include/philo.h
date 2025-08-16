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
# include "../include/colors.h"
# include "../include/struct.h"

/* Prototypes */

int		main(int ac, char **av);
int		parser(int ac, char **av);
int		init(char **av, t_data *data);
void	print_error(char *msg);

int		thread_handler(pthread_t *thread, void *(*thread_routine)(void *), void *data, t_thread_code num_thread);
int		mutex_handler(t_mtx *mutex, t_mtx_code num_mtx);
void    set_val(t_mtx *mutex, long *dest, long value);
long	get_val(t_mtx *mutex, long *value);
int		simulation_finished(t_data *data);
int		simulation(t_data *data);
void	wait_all_threads(t_data *data);
int		_usleep(t_data *data, int usec);
long	gettime(t_time_code time_code);
void	message_status(t_philo *philo, t_philo_status status);
void	*monitor_routine(void *arg);
void	increment_synch_var(t_mtx *mutex, long *value);
int		all_philo_running(t_mtx *mutex, long *philos, long philo_nbr);

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_isdigit(int c);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
int		ft_strcmp(char *s1, char *s2);

#endif
