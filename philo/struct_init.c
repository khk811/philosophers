#include "philo.h"

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

	// info = t_info_alloc(info, args);
	// if (!info)
	// 	return (0);
	gettimeofday(&(info->start), NULL);
	if (!t_info_mutex_init(info, args))
		return (free_t_info(info));
	i = 0;
	while (i < args->philo_num)
		(info->fork_arr)[i++] = 1;
	info->death_flag = 0;
	info->hungry_philo = args->philo_num;
	return (1);
}

int	philos_init(t_args *args, t_info *info, t_philo **philos)
{
	// t_philo	*philos;
	int		i;

	// philos = t_philo_alloc(args);
	// if (!philos)
	// 	return (NULL);
	i = 0;
	while (i < args->philo_num)
	{
		(*philos)[i].id = i;
		(*philos)[i].eat_count = args->num_of_must_eat;
		gettimeofday(&((*philos)[i].last_meal), NULL);
		(*philos)[i].is_dead = 0;
		(*philos)[i].info = info;
		(*philos)[i].args = args;
		pthread_create(&((*philos)[i].philo), NULL, philos_simulation, (void *)(&((*philos)[i])));
		i++;
	}
	return (1);
}
