/* Stuctures */

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
	int		initialized;
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
	long		id;
	long		last_meal_time;//the time pqssed from last meal
	long		meals_counter;
	long		full;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;// each philo is a thread
	t_mtx		philo_mutex;// avoid races with monitor
	t_data		*data;
}	t_philo;

struct s_data
{
	long		philos_number;
	long		time_to_eat;
	long		time_to_die;
	long		time_to_sleep;
	long		nmr_limit_meals;// [7] | flag
	long		start_simulation;
	long		all_thread_ready;//thread synchnonisation
	long		end_simulation;//when a philo dies or all full
	long		philos_running_nbr;// this var for the monitor purpuse
	pthread_t	monitor;
	t_mtx		data_mutex;//protection from races while rading from data
	t_mtx		msg_mutex;//protection when writing in message
	t_fork		*forks;//array of forks
	t_philo		*philos;//array of philo
};
