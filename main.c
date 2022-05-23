/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:02:51 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/23 13:13:21 by hyunkkim         ###   ########seoul.kr  */
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

size_t	get_milisecond(int sec, int usec)
{
	return ((sec * 1000) + (usec / 1000));
}

size_t	make_timestamp(struct timeval *start)
{
	struct timeval	curr;
	size_t	curr_time;
	size_t	start_time;

	gettimeofday(&curr, NULL);
	curr_time = get_milisecond(curr.tv_sec, curr.tv_usec);
	start_time = get_milisecond(start->tv_sec, start->tv_usec);
	return (curr_time - start_time);
}

int	should_philo_die(t_philo *philo)
{
	int	starve_time;

	starve_time = (int)make_timestamp(philo->last_meal);
	if (philo->args->time_to_die <= starve_time)
		philo->is_dead = 1;
	return (philo->is_dead);
}

void	print_statement(t_philo *philo, char *s)
{
	pthread_mutex_lock(philo->info->print);
	printf("%zu %d %s\n", make_timestamp(philo->info->start), philo->id, s);
	pthread_mutex_unlock(philo->info->print);
}

void	*philos_simulation(void *philo)
{
	t_philo	*the_philo;

	the_philo = (t_philo *)philo;
	while (!(the_philo->is_dead))
	{
		if (grep_forks(the_philo))
			break ;
		if (eat_spaghetti(the_philo))
			break ;
		leave_forks(the_philo);
		if (sleep_after_diner(the_philo))
			break ;
		print_statement(the_philo, "is thinking");
	}
	if (the_philo->is_dead)
		print_statement(the_philo, "died");
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
	parse_input(&args, argc, argv);
	info = t_info_init(args);
	printf("<< total philo_num : %d>>\n\n", args->philo_num);
	philos = philos_init(args, info);
	i = 0;
	while (i < args->philo_num)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
	return (0);
}
