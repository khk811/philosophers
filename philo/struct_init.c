#include "philo.h"

t_args	*t_args_init(void)
{
	t_args	*new;

	new = malloc(sizeof(t_args));
	if (!new)
		return (NULL);
	new->philo_num = 0;
	new->time_to_die = 0;
	new->time_to_eat = 0;
	new->time_to_sleep = 0;
	new->num_of_must_eat = -1;
	return (new);
}

static pthread_mutex_t	*fork_init(t_args *args)
{
	pthread_mutex_t	*forks;
	int				num;

	num = args->philo_num;
	forks = malloc(sizeof(pthread_mutex_t) * num);
	if (!forks)
		return (NULL);
	num = 0;
	while (num < args->philo_num)
	{
		pthread_mutex_init(&forks[num], NULL);
		num++;
	}
	return (forks);
}

t_info	*t_info_init(t_args *args)
{
	t_info	*new;
	int		i;

	new = malloc(sizeof(t_info));
	if (!new)
		return (NULL);
	new->start = malloc(sizeof(struct timeval));
	if (!(new->start))
	{
		free(new);
		new = NULL;
		return (NULL);
	}
	gettimeofday(new->start, NULL);
	new->forks = fork_init(args);
	pthread_mutex_init(&(new->print), NULL);
	pthread_mutex_init(&(new->start_line), NULL);
	pthread_mutex_init(&(new->death), NULL);
	pthread_mutex_init(&(new->full), NULL);
	new->death_flag = 0;
	new->hungry_philo = args->philo_num;
	new->fork_arr = malloc(sizeof(int) * args->philo_num);
	i = 0;
	while (i < args->philo_num)
	{
		(new->fork_arr)[i] = 1;
		i++;
	}
	return (new);
}

t_philo	*philos_init(t_args *args, t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * (args->philo_num));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < args->philo_num)
	{
		(philos[i]).id = i;
		(philos[i]).eat_count = args->num_of_must_eat;
		(philos[i]).last_meal = malloc(sizeof(struct timeval));
		gettimeofday(philos[i].last_meal, NULL);
		(philos[i]).is_dead = 0;
		(philos[i]).info = info;
		(philos[i]).args = args;
		pthread_create(&(philos[i].philo), NULL, philos_simulation, (void *)(&philos[i]));
		i++;
	}
	return (philos);
}