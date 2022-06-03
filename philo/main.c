/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:02:51 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 16:54:29 by hyunkkim         ###   ########seoul.kr  */
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
}

size_t	get_milisecond(int sec, int usec)
{
	return ((sec * 1000) + (usec / 1000));
}

size_t	make_timestamp(struct timeval start)
{
	struct timeval	curr;
	size_t	curr_time;
	size_t	start_time;

	gettimeofday(&curr, NULL);
	curr_time = get_milisecond(curr.tv_sec, curr.tv_usec);
	start_time = get_milisecond(start.tv_sec, start.tv_usec);
	// printf("%zu - %zu\n", curr_time, start_time);
	return (curr_time - start_time);
}

void	usleep_accurately(struct timeval stamp, int usleep_duration)
{
	usleep(usleep_duration * 900);
	while (1)
	{
		if ((int)make_timestamp(stamp) >= usleep_duration)
			break ;
		usleep(150);
	}
}

int	should_philo_die(t_philo *philo)
{
	int	starve_time;

	starve_time = (int)make_timestamp(philo->last_meal);
	if (philo->args->time_to_die <= starve_time)
	{
		pthread_mutex_lock(&(philo->info->death));
		philo->info->death_flag = 1;
		pthread_mutex_unlock(&(philo->info->death));
		usleep(100);
		pthread_mutex_lock(&(philo->info->print));
		printf("%zu %d died\n", make_timestamp(philo->info->start), philo->id);
		pthread_mutex_unlock(&(philo->info->print));
	}
	return (philo->info->death_flag);
}

int	is_philo_full(t_philo *philo)
{
	if (philo->eat_count == 0)
	{
		pthread_mutex_lock(&(philo->info->full));
		(philo->info->hungry_philo)--;
		pthread_mutex_unlock(&(philo->info->full));
		return (1);
	}
	return (0);
}

void	print_statement(t_philo *philo, char *s)
{
	pthread_mutex_lock(&(philo->info->print));
	if (!check_death_flag(philo->info))
		printf("%zu %d %s\n", make_timestamp(philo->info->start), philo->id, s);
	pthread_mutex_unlock(&(philo->info->print));
}

int	check_death_flag(t_info *info)
{
	int	ret;

	pthread_mutex_lock(&(info->death));
	ret = info->death_flag;
	pthread_mutex_unlock(&(info->death));
	return (ret);
}

void	*philos_simulation(void *philo)
{
	t_philo	*the_philo;

	the_philo = (t_philo *)philo;
	pthread_mutex_lock(&(the_philo->info->start_line));
	pthread_mutex_unlock(&(the_philo->info->start_line));
	if (the_philo->id % 2 == 1)
		usleep(1500);
	while (!check_death_flag(the_philo->info))
	{
		// if (grep_forks(the_philo))
		// 	break ;
		if (eat_spaghetti(the_philo))
			break ;
		// leave_forks(the_philo);
		if (is_philo_full(the_philo))
			break ;
		if (sleep_after_diner(the_philo))
			break ;
		if (!check_death_flag(the_philo->info))
			print_statement(the_philo, "is thinking");
		usleep(200);
	}
	return (NULL);
}

int	parse_input(t_args *args, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		(args)->philo_num = ft_atoi(argv[1]);
		(args)->time_to_die = ft_atoi(argv[2]);
		(args)->time_to_eat = ft_atoi(argv[3]);
		(args)->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			(args)->num_of_must_eat = ft_atoi(argv[5]);
		else
			args->num_of_must_eat = -1;
	}
	if (args->philo_num < 1 || args->time_to_die < 1 || args->time_to_eat < 1 || \
	args->time_to_sleep < 1 || args->num_of_must_eat == 0)
		return (0);
	else
		return (1);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_info	info;
	t_philo	*philos;
	int	i;
	int	success_thread_num;

	if (!parse_input(&args, argc, argv))
		return (1);
	if (!alloc_info_n_philos(&info, &philos, &args))
		return (1);
	if (!t_info_init(&info, &args))
	{
		free_info_n_philos(&info, &philos);
		return (1);
	}
	printf(">> %zu\n", make_timestamp(info.start));
	printf("<< total philo_num : %d>>\n\n", args.philo_num);
	// lock start line;
	pthread_mutex_lock(&(info.start_line));
	// philos = philos_init(&args, &info);
	success_thread_num = philos_init(&args, &info, philos);
	if (success_thread_num != args.philo_num)
		info.death_flag = 1;
	// unlock start line;
	pthread_mutex_unlock(&(info.start_line));
	i = 0;
	while (info.death_flag == 0)
	{
		if (should_philo_die(&philos[i]) && !is_philo_full(&philos[i]))
		{
			printf("%zu spand\n", make_timestamp(philos[i].last_meal));
			break ;
		}
		if (info.hungry_philo == 0)
		{
			printf("Philos are full. end of program\n");
			break ;
		}
		i++;
		if (i == args.philo_num)
			i = 0;
		usleep(150);
	}
	i = 0;
	while (i < success_thread_num)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
	printf("success thread num : %d\n", i);
	// system("leaks philo");
	return (0);
}
