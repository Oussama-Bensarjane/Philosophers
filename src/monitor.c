#include "../include/philo.h"

void *monitor_routine(void *arg)
{
    t_data *data;
    int i;
	int all_full;
	long last_meal;
	long now;

	data = (t_data *)arg;
    while (!simulation_finished(data))
    {
        i = -1;
        while (++i < data->philos_number && !simulation_finished(data))
        {
            last_meal = get_val(&data->philos[i].philo_mutex, &data->philos[i].last_meal_time);
            now = gettime(MILISEC);
            if ((now - last_meal) > (data->time_to_die / 1000)) // convert usec → ms cz in init i converted all to micro for usleep !
            {
                message_status(&data->philos[i], DIED);
                set_val(&data->data_mutex, &data->end_simulation, 1);
                return NULL;
            }
        }

        if (data->nmr_limit_meals > 0)
        {
            all_full = 1;
			i = -1;
            while (++i < data->philos_number)
            {
                if (!get_val(&data->philos[i].philo_mutex, &data->philos[i].full))
                {
                    all_full = 0;
                    break;
                }
            }
            if (all_full)
                set_val(&data->data_mutex, &data->end_simulation, 1);
        }
        usleep(1000); // wait 1 ms for check
    }
    return NULL;
}

