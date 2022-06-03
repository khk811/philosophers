/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:20:43 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 17:22:29 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_t_info(t_info *info, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_num)
		pthread_mutex_destroy(&(info->forks[i++]));
	if (info->forks)
		free(info->forks);
	if (info->fork_arr)
		free(info->fork_arr);
	pthread_mutex_destroy(&(info->print));
	pthread_mutex_destroy(&(info->death));
	pthread_mutex_destroy(&(info->start_line));
	pthread_mutex_destroy(&(info->full));
	return (0);
}

int	free_info_n_philos(t_info *info, t_philo **philos, t_args *args)
{
	free_t_info(info, args);
	free(*philos);
	return (0);
}

int	alloc_info_n_philos(t_info *info, t_philo **philos, t_args *args)
{
	info->forks = malloc(sizeof(pthread_mutex_t) * args->philo_num);
	info->fork_arr = malloc(sizeof(int) * args->philo_num);
	if (!(info->forks) || !(info->fork_arr))
	{
		free_t_info(info, args);
		return (0);
	}
	*philos = malloc(sizeof(t_philo) * args->philo_num);
	if (!(*philos))
		return (0);
	return (1);
}
