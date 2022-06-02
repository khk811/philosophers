/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:53:35 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/02 16:14:01 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*t_info_alloc(t_args *args)
{
	t_info	*new;

	new = malloc(sizeof(t_info));
	if (!new)
		return (NULL);
	new->start = malloc(sizeof(struct timeval));
	new->forks = malloc(sizeof(pthread_mutex_t) * args->philo_num);
	new->fork_arr = malloc(sizeof(int) * args->philo_num);
	if (!new->start || !new->forks || !new->fork_arr)
	{
		if (new->start)
			free(new->start);
		if (new->forks)
			free(new->forks);
		if (new->fork_arr)
			free(new->fork_arr);
		new->start = NULL;
		new->forks = NULL;
		new->fork_arr = NULL;
		free(new);
		new = NULL;
	}
	return (new);
}

t_philo	*t_philo_alloc(t_args *args)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * args->philo_num);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < args->philo_num)
	{
		philos[i].last_meal = malloc(sizeof(struct timeval));
		if (!(philos[i].last_meal))
		{
			while ((i + 1))
			{
				free(philos[i].last_meal);
				philos[i].last_meal = NULL;
				i--;
			}
			free(philos);
			philos = NULL;
			break ;
		}
		i++;
	}
	return (philos);
}
