/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obensarj <obensarj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:00:04 by obensarj          #+#    #+#             */
/*   Updated: 2025/08/11 18:27:59 by obensarj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 * get_and_set are getters and setters module
 * basicly avoid writing to LOCK and UNLOCK  
*/

void    set_val(t_mtx *mutex, long *dest, long value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

long    get_val(t_mtx *mutex, long *value)
{
	long ret;

	mutex_handler(mutex, LOCK);
	ret = *value;
	mutex_handler(mutex, UNLOCK);
	return (ret);
}

int	simulation_finished(t_data *data)
{
	return (get_val(&data->data_mutex, &data->end_simulation));
}
