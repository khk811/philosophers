/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:02:51 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 18:21:51 by hyunkkim         ###   ########seoul.kr  */
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
		if (eat_spaghetti(the_philo))
			break ;
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
	if (args->philo_num < 1 || args->time_to_die < 1 || \
	args->time_to_eat < 1 || args->time_to_sleep < 1 || \
	args->num_of_must_eat == 0)
		return (0);
	else
		return (1);
}

void	watch_philos(t_args *args, t_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	while (info->death_flag == 0)
	{
		if (should_philo_die(&philos[i]) && !is_philo_full(&philos[i]))
			break ;
		if (info->hungry_philo == 0)
		{
			printf("Philos are full. end of program\n");
			break ;
		}
		i++;
		if (i == args->philo_num)
			i = 0;
		usleep(150);
	}
}

int	prep_struct(t_args *args, t_info *info, t_philo **philos)
{
	if (!alloc_info_n_philos(info, philos, args))
		return (0);
	if (!t_info_init(info, args))
	{
		free_info_n_philos(info, philos, args);
		return (0);
	}
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
	if (!prep_struct(&args, &info, &philos))
		return (1);
	pthread_mutex_lock(&(info.start_line));
	success_thread_num = philos_init(&args, &info, philos);
	if (success_thread_num != args.philo_num)
		info.death_flag = 1;
	pthread_mutex_unlock(&(info.start_line));
	watch_philos(&args, &info, philos);
	i = 0;
	while (i < success_thread_num)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
	free_info_n_philos(&info, &philos, &args);
	return (0);
}
