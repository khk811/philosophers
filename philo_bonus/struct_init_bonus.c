/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:34:46 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/06 14:47:52 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	t_philo_init(t_philo *philo)
{
	sem_unlink("forks");
	sem_unlink("print");
	philo->forks = sem_open("forks", O_CREAT, 0644, \
	(unsigned int)(philo->philo_num));
	philo->print = sem_open("print", O_CREAT, 0644, 1);
	gettimeofday(&(philo->start), NULL);
	gettimeofday(&(philo->last_meal), NULL);
	return (1);
}
