#include "../include/philo.h"

void cleanup(t_data *data)
{
    int i;

    if (!data)
        return ;
    //  dest fork mutexes
    i = -1;
    while (++i < data->philos_number && data->forks)
    {
        if (data->forks[i].initialized)
        {
            mutex_handler(&data->forks[i].fork, DESTROY);
            data->forks[i].initialized = 0;
        }
    }
    // dest philosopher mutexes
    i = -1;
    while (++i < data->philos_number && data->philos)
        mutex_handler(&data->philos[i].philo_mutex, DESTROY);

    // // dest global mutexes
    mutex_handler(&data->data_mutex, DESTROY);
    mutex_handler(&data->msg_mutex, DESTROY);

    //  f allocated mem
    if (data->philos)
        free(data->philos);
    if (data->forks)
        free(data->forks);
}