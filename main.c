/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:02:51 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/17 21:34:07 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test_mutex(void *philo)
{
	t_philo	*the_philo;

	the_philo = (t_philo *)philo;
	// forks(mutex) test area;
	pthread_mutex_lock(&(the_philo->info->forks[1]));
	pthread_mutex_lock(&(the_philo->info->forks[3]));
	printf("philo[%d] is eating\n", the_philo->id);
	usleep((the_philo->args->time_to_eat) * 1000);
	pthread_mutex_unlock(&(the_philo->info->forks[3]));
	pthread_mutex_unlock(&(the_philo->info->forks[1]));
	printf("philo[%d] is sleeping\n", the_philo->id);
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
	struct timeval	curr;
	t_philo	test_philo;
	//pthread_t	*philos;

	args = t_args_init();
	info = t_info_init(args);
	printf("argc : %d\n", argc);
	parse_input(&args, argc, argv);
	printf("philo_num : %d\n", args->philo_num);
	usleep(1000 * 1000);
	gettimeofday(&curr, NULL);
	printf("curr - start : %f sec\n", (double)(curr.tv_sec - info->start->tv_sec));
	test_philo.args = args;
	test_philo.info = info;
	test_philo.id = 2;
	test_philo.eat_count = 0;
	test_philo.death = args->time_to_die;
	pthread_create(&(test_philo.philo), NULL, test_mutex, (void *)(&test_philo));
	pthread_join(test_philo.philo, NULL);
	return (0);
}
