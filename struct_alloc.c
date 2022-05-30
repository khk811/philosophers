/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:53:35 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/26 14:25:27 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*t_args_alloc(void)
{
	t_args	*new;

	new = malloc(sizeof(t_args));
	if (!new)
		return (NULL);
	return (new);
}

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
		// free all return null;
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
		i++;
	}
}
