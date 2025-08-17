/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 08:55:19 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/17 07:53:59 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
void f(void)
{
	system("leaks philo");
}
int	main(int ac, char **av)
{
	atexit(f);
	t_data	data;
 
	if (parser(ac, av))
		return (1);
	if (init(av, &data))
		return (cleanup(&data), 1);
	simulation(&data);
	cleanup(&data);
	return (0);
}
