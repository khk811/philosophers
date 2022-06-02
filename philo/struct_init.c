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

t_info	*t_info_alloc(t_args *args)
{
	t_info	*new;

	new = malloc(sizeof(t_info));
	if (!new)
		return (NULL);
	new->start = malloc(sizeof(struct timeval));
	new->forks = malloc(sizeof(pthread_mutex_t) * args->philo_num);
	new->fork_arr = malloc(sizeof(int) * args->philo_num);
	if (!new->start || !new->forks || !new->fork_arr)
	{
		if (new->start)
			free(new->start);
		if (new->forks)
			free(new->forks);
		if (new->fork_arr)
			free(new->fork_arr);
		new->start = NULL;
		new->forks = NULL;
		new->fork_arr = NULL;
		free(new);
		new = NULL;
	}
	return (new);
}

t_info	*t_info_init(t_args *args)
{
	t_info	*new;
	int		i;

	new = t_info_alloc(args);
	if (!new)
		return (NULL);
	gettimeofday(new->start, NULL);
	// new->forks = fork_init(args);
	i = 0;
	while (i < args->philo_num)
		pthread_mutex_init(&(new->forks[i++]), NULL);
	i = 0;
	while (i < args->philo_num)
		(new->fork_arr)[i++] = 1;
	pthread_mutex_init(&(new->print), NULL);
	pthread_mutex_init(&(new->death), NULL);
	new->death_flag = 0;
	pthread_mutex_init(&(new->start_line), NULL);
	pthread_mutex_init(&(new->full), NULL);
	new->hungry_philo = args->philo_num;
	return (new);
}

t_philo	*t_philo_alloc(t_args *args)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * args->philo_num);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < args->philo_num)
	{
		philos[i].last_meal = malloc(sizeof(struct timeval));
		if (!(philos[i].last_meal))
		{
			while ((i + 1))
			{
				free(philos[i].last_meal);
				philos[i].last_meal = NULL;
				i--;
			}
			free(philos);
			philos = NULL;
			break ;
		}
		i++;
	}
	return (philos);
}

t_philo	*philos_init(t_args *args, t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = t_philo_alloc(args);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < args->philo_num)
	{
		(philos[i]).id = i;
		(philos[i]).eat_count = args->num_of_must_eat;
		// (philos[i]).last_meal = malloc(sizeof(struct timeval));
		gettimeofday(philos[i].last_meal, NULL);
		(philos[i]).is_dead = 0;
		(philos[i]).info = info;
		(philos[i]).args = args;
		pthread_create(&(philos[i].philo), NULL, philos_simulation, (void *)(&philos[i]));
		i++;
	}
	return (philos);
}
