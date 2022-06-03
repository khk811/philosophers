/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:03:09 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 20:03:10 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

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

	gettimeofday(&(info->start), NULL);
	if (!t_info_mutex_init(info, args))
		return (free_t_info(info, args));
	i = 0;
	while (i < args->philo_num)
		(info->fork_arr)[i++] = 1;
	info->death_flag = 0;
	info->hungry_philo = args->philo_num;
	return (1);
}

int	philos_init(t_args *args, t_info *info, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < args->philo_num)
	{
		philos[i].id = i;
		philos[i].eat_count = args->num_of_must_eat;
		gettimeofday(&((philos)[i].last_meal), NULL);
		philos[i].is_dead = 0;
		philos[i].info = info;
		philos[i].args = args;
		if (pthread_create(&(philos[i].philo), NULL, feed_philos, \
		(void *)(&(philos[i]))) != 0)
			return (i);
		i++;
	}
	return (i);
}
