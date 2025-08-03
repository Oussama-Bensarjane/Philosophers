#ifndef PHILO_H
#define PHILO_H

# define USAGE "Usage: (ONLY POSITIVE INTEGERS!)\n./philo nbr_of_philos time_to_die time_to_eat time_to_sleep [nbr_of_times_each_philos_must_eat]\n"

# include <unistd.h>
# include <stdio.h>

int		main(int ac, char **av);
int		parser(int ac, char **av);
void    print_error_usage(char *msg, int fd);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int     ft_isdigit(int c);
int	    ft_strlen(char *str);
int     ft_atoi(const char *str);

#endif
