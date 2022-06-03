/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:20:43 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 16:16:03 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_t_info(t_info *info)
{
	// if (info->start)
	// 	free(info->start);
	if (info->forks)
		free(info->forks);
	if (info->fork_arr)
		free(info->fork_arr);
	return (0);
}

t_info	*t_info_alloc(t_info *info, t_args *args)
{
	// info->start = malloc(sizeof(struct timeval));
	info->forks = malloc(sizeof(pthread_mutex_t) * args->philo_num);
	info->fork_arr = malloc(sizeof(int) * args->philo_num);
	if (!(info->forks) || !(info->fork_arr))
	{
		free_t_info(info);
		return (NULL);
	}
	return (info);
}

int	free_philos(t_philo **philos)
{
	// int	i;

	// i = 0;
	// while (i < args->philo_num)
	// {
	// 	if ((*philos)[i].last_meal)
	// 		free((*philos)[i].last_meal);
	// 	i++;
	// }
	free(*philos);
	return (0);
}

t_philo	*philos_alloc(t_args *args)
{
	t_philo	*philos;
	// int		i;

	philos = malloc(sizeof(t_philo) * args->philo_num);
	if (!philos)
		return (NULL);
	// i = 0;
	// while (i < args->philo_num)
	// {
	// 	philos[i].last_meal = malloc(sizeof(struct timeval));
	// 	if (!(philos[i].last_meal))
	// 	{
	// 		free_philos(&philos, args);
	// 		return (NULL);
	// 	}
	// 	i++;
	// }
	return (philos);
}
