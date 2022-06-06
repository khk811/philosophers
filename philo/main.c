/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:02:51 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/06 15:59:02 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*feed_philos(void *philo)
{
	t_philo	*the_philo;

	the_philo = (t_philo *)philo;
	pthread_mutex_lock(&(the_philo->info->start_line));
	pthread_mutex_unlock(&(the_philo->info->start_line));
	if (the_philo->id % 2 == 1)
		usleep(1500);
	while (!did_someone_die(the_philo->info))
	{
		if (eat_spaghetti(the_philo))
			break ;
		if (is_philo_full(the_philo))
			break ;
		if (sleep_after_diner(the_philo))
			break ;
		if (!did_someone_die(the_philo->info))
			print_status(the_philo, "is thinking");
		usleep(200);
	}
	return (NULL);
}

void	watch_philos(t_args *args, t_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	while (info->death_flag == 0)
	{
		if (should_philo_die(&philos[i]) && !is_philo_full(&philos[i]))
			break ;
		pthread_mutex_lock(&(info->full));
		if (info->hungry_philo == 0)
		{
			printf("All philosophers ate well. The end\n");
			pthread_mutex_unlock(&(info->full));
			break ;
		}
		pthread_mutex_unlock(&(info->full));
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
	int		i;
	int		success_thread_num;

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
		pthread_join(philos[i++].philo, NULL);
	free_info_n_philos(&info, &philos, &args);
	return (0);
}
