#include "../include/philo.h"

void cleanup(t_data *data)
{
    int i;

    // i = -1;
    // while (++i < data->philos_number)
    // {
	// 	printf("cleanup: joining philo %d thread_id=%lu\n", i, data->philos[i].thread_id);

    //     if (data->philos[i].thread_id != 0) // make sure thread exists
    //         pthread_join(data->philos[i].thread_id, NULL);
    // }

    //  dest fork mutexes
    i = -1;
    while (++i < data->philos_number)
        pthread_mutex_destroy(&data->forks[i].fork);

    // dest philosopher mutexes
    i = -1;
    while (++i < data->philos_number)
        pthread_mutex_destroy(&data->philos[i].philo_mutex);

    // dest global mutexes
    pthread_mutex_destroy(&data->data_mutex);
    pthread_mutex_destroy(&data->msg_mutex);

    //  f allocated mem
    if (data->philos)
        free(data->philos);
    if (data->forks)
        free(data->forks);
}

