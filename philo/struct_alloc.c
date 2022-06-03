/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:20:43 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 16:36:01 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_t_info(t_info *info)
{
	if (info->forks)
		free(info->forks);
	if (info->fork_arr)
		free(info->fork_arr);
	return (0);
}

int	free_info_n_philos(t_info *info, t_philo **philos)
{
	free_t_info(info);
	free(*philos);
	return (0);
}
/*
t_info	*t_info_alloc(t_info *info, t_args *args)
{
	info->forks = malloc(sizeof(pthread_mutex_t) * args->philo_num);
	info->fork_arr = malloc(sizeof(int) * args->philo_num);
	if (!(info->forks) || !(info->fork_arr))
	{
		free_t_info(info);
		return (NULL);
	}
	return (info);
}


t_philo	*philos_alloc(t_args *args)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * args->philo_num);
	if (!philos)
		return (NULL);
	return (philos);
}
*/
int	alloc_info_n_philos(t_info *info, t_philo **philos, t_args *args)
{
	info->forks = malloc(sizeof(pthread_mutex_t) * args->philo_num);
	info->fork_arr = malloc(sizeof(int) * args->philo_num);
	if (!(info->forks) || !(info->fork_arr))
	{
		free_t_info(info);
		return (0);
	}
	*philos = malloc(sizeof(t_philo) * args->philo_num);
	if (!(*philos))
		return (0);
	return (1);
}
