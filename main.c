/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:02:51 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/19 14:05:58 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	decide_fork_priority(t_philo *philo, int *right, int *left)
{
	int	id;
	int	num;

	id = philo->id;
	num = philo->args->philo_num;
	if (id % 2 == 0)
	{
		*right = ((num - 1) + id) % num;
		*left = id;
	}
	else
	{
		*right = id;
		*left = ((num - 1) + id) % num;
	}
}

int	make_timestamp(struct timeval *start)
{
	struct timeval	curr;
	int	timestamp;

	gettimeofday(&curr, NULL);
	timestamp = (curr.tv_usec - start->tv_usec);
	return (timestamp);
}

void	*take_forks(void *philo)
{
	t_philo	*the_philo;
	int		right_fork;
	int		left_fork;

	the_philo = (t_philo *)philo;
	decide_fork_priority(the_philo, &right_fork, &left_fork);
	pthread_mutex_lock(&(the_philo->info->forks[right_fork]));
	pthread_mutex_lock(&(the_philo->info->forks[left_fork]));
	printf("%d(us) %d is eating\n", make_timestamp(the_philo->info->start), the_philo->id);
	usleep((the_philo->args->time_to_eat) * 1000);
	pthread_mutex_unlock(&(the_philo->info->forks[left_fork]));
	pthread_mutex_unlock(&(the_philo->info->forks[right_fork]));
	printf("%d(us) %d is sleeping\n", make_timestamp(the_philo->info->start), the_philo->id);
	usleep((the_philo->args->time_to_sleep) * 1000);
	return (NULL);
}

void	parse_input(t_args **args, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		(*args)->philo_num = ft_atoi(argv[1]);
		(*args)->time_to_die = ft_atoi(argv[2]);
		(*args)->time_to_eat = ft_atoi(argv[3]);
		(*args)->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			(*args)->num_of_must_eat = ft_atoi(argv[5]);
	}
}

int	main(int argc, char **argv)
{
	t_args	*args;
	t_info	*info;
	t_philo	*philos;
	int	i;

	args = t_args_init();
	info = t_info_init(args);
	parse_input(&args, argc, argv);
	printf("<< total philo_num : %d>>\n\n", args->philo_num);
	philos = philo_on_the_table(args, info);
	i = 0;
	while (i < args->philo_num)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
	return (0);
}
