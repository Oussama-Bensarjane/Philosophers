/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 08:55:13 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/11 21:18:43 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

int	ft_atoi(char *str)
{
	long	nbr;
	long	tmp;
	int		sign;

	nbr = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		tmp = nbr;
		nbr = (nbr * 10) + (*str++ - '0');
		if ((nbr / 10) != tmp && sign == 1)
			return (-1);
		else if ((nbr / 10) != tmp && sign == -1)
			return (0);
	}
	return (nbr * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && \
		((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

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
