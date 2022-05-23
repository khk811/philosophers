/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:02:51 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/23 21:41:06 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	decide_fork_priority(t_philo *philo, int *right, int *left)
{
	int	id;
	int	num;

	id = philo->id;
	num = philo->args->philo_num;
	*right = id;
	*left = ((num - 1) + id) % num;
	/*
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
	*/
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
	{
		printf("philo %d >> %zu\n", philo->id, make_timestamp(philo->last_meal));
		philo->is_dead = 1;
	}
	return (philo->is_dead);
}

void	print_statement(t_philo *philo, char *s)
{
	pthread_mutex_lock(philo->info->print);
	printf("%zu %d %s\n", make_timestamp(philo->info->start), philo->id, s);
	pthread_mutex_unlock(philo->info->print);
}

int	check_death_flag(t_info *info)
{
	int	ret;

	pthread_mutex_lock(info->death);
	ret = info->death_flag;
	pthread_mutex_unlock(info->death);
	return (ret);
}

void	*philos_simulation(void *philo)
{
	t_philo	*the_philo;

	// ??? lock start line;
	// unlock start line;
	// id % 2 == 1
	// usleep (1000 ~ 2000);
	the_philo = (t_philo *)philo;
	pthread_mutex_lock(the_philo->info->start_line);
	pthread_mutex_unlock(the_philo->info->start_line);
	if (the_philo->id % 2 == 1)
		usleep(1500);
	while (!check_death_flag(the_philo->info))
	{
		if (grep_forks(the_philo))
			break ;
		if (eat_spaghetti(the_philo))
			break ;
		leave_forks(the_philo);
		if (sleep_after_diner(the_philo))
			break ;
		if (!check_death_flag(the_philo->info))
			print_statement(the_philo, "is thinking");
		usleep(200);
	}
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
	// lock start line;
	pthread_mutex_lock(info->start_line);
	philos = philos_init(args, info);
	// unlock start line;
	pthread_mutex_unlock(info->start_line);
	i = 0;
	while (info->death_flag == 0)
	{
		if (should_philo_die(&philos[i]))
		{
			pthread_mutex_lock(info->death);
			info->death_flag = 1;
			pthread_mutex_unlock(info->death);
			print_statement(&philos[i], "died");
			// printf("%zu spand", make_timestamp(philos[i].last_meal));
			break ;
		}
		i++;
		if (i == args->philo_num)
			i = 0;
	}
	i = 0;
	while (i < args->philo_num)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
	return (0);
}
