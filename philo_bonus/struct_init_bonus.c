/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:34:46 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/02 16:53:06 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
/*
int	total_alloc(t_philo *philo, pid_t **philos_pid)
{
	philo->start = malloc(sizeof(struct timeval));
	philo->last_meal = malloc(sizeof(struct timeval));
	(*philos_pid) = malloc(sizeof(pid_t) * philo->philo_num);
	if (!(philo->start) || !(philo->last_meal) || !(philos_pid))
	{
		if (philo->start)
			free(philo->start);
		if (philo->last_meal)
			free(philo->last_meal);
		if (*philos_pid)
			free(philos_pid);
		philo->start = NULL;
		philo->last_meal = NULL;
		(*philos_pid) = NULL;
		return (0);
	}
	return (1);
}
*/
int	t_philo_init(t_philo *philo)
{
	sem_unlink("forks");
	sem_unlink("print");
	philo->forks = sem_open("forks", O_CREAT, 0644, (unsigned int)(philo->philo_num));
	philo->print = sem_open("print", O_CREAT, 0644, 1);
	gettimeofday(&(philo->start), NULL);
	gettimeofday(&(philo->last_meal), NULL);
	return (1);
}
