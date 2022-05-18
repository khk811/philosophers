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
	new->num_of_must_eat = 0;
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
		pthread_mutex_init(&(forks[num]), NULL);
		num++;
	}
	return (forks);
}

t_info	*t_info_init(t_args *args)
{
	t_info	*new;

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
	return (new);
}
