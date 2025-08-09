/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 08:55:23 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/09 11:38:34 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INPUT "Wrong Or Incomplete Input \n"
# define USAGE0 "Usage: (ONLY POSITIVE INTEGERS!)\n"
# define USAGE1 "./philo nbr_of_philos time_to_die time_to_eat time_to_sleep \
[nbr_of_times_each_philos_must_eat]\n"
# define EXMPL "For Example : ----> ./philo 5 80 100 40 [7]\n"
# define PHILO "Number of Philos should be at least 1 \n"

# define INIT "Failed to initiat \n"

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
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
** ./philo 5 600 500 40 [7]
*/

typedef struct s_philo
{
	int			id;
	int			last_meal_time;//the time pqssed from last meal
	int			meals_counter;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;// each philo is a thread
	t_data		*data;
}	t_philo;

struct s_data
{
	int		philos_number;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		nmr_limit_meals;// [7] | flag
	int		start_simulation;
	int		end_simulation;//when a philo dies or all full
	t_fork	*fork;//array of forks
	t_philo	*philos;//array of philo
};

/* Prototypes */

int		main(int ac, char **av);
int		parser(int ac, char **av);
void	print_error(char *msg);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
int		ft_strcmp(char *s1, char *s2);

#endif
