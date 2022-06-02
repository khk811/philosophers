#include "philo.h"

int	free_t_info(t_info *info)
{
	if (info->start)
		free(info->start);
	if (info->forks)
		free(info->forks);
	if (info->fork_arr)
		free(info->fork_arr);
	return (0);
}

t_info	*t_info_alloc(t_info *info, t_args *args)
{
	info->start = malloc(sizeof(struct timeval));
	info->forks = malloc(sizeof(pthread_mutex_t) * args->philo_num);
	info->fork_arr = malloc(sizeof(int) * args->philo_num);
	if (!info->start || !info->forks || !info->fork_arr)
		return (NULL);
	return (info);
}

int	t_info_mutex_init(t_info *info, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_num)
	{
		if (pthread_mutex_init(&(info->forks[i++]), NULL) != 0)
			return (0);
	}
	if (pthread_mutex_init(&(info->print), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->death), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->start_line), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->full), NULL) != 0)
		return (0);
	return (1);
}

int	t_info_init(t_info *info, t_args *args)
{
	int		i;

	info = t_info_alloc(info, args);
	if (!info)
		return (0);
	gettimeofday(info->start, NULL);
	if (!t_info_mutex_init(info, args))
		return (free_t_info(info));
	i = 0;
	while (i < args->philo_num)
		(info->fork_arr)[i++] = 1;
	info->death_flag = 0;
	info->hungry_philo = args->philo_num;
	return (1);
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
