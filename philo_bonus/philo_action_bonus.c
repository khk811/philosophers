/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:12:09 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/06 15:48:40 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	grab_fork(t_philo *philo)
{
	if (should_philo_die(philo))
		return (0);
	else
	{
		sem_wait(philo->forks);
		print_status(philo, "has taken a fork");
		sem_wait(philo->forks);
		print_status(philo, "has taken a fork");
		return (1);
	}
}

void	leave_fork(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	eat_spaghetti(t_philo *philo)
{
	struct timeval	duration;

	if (!should_philo_die(philo))
	{
		if (!grab_fork(philo))
			return ;
		gettimeofday(&duration, NULL);
		gettimeofday(&(philo->last_meal), NULL);
		if (!should_philo_die(philo))
			print_status(philo, "is eating");
		(philo->num_of_must_eat)--;
		usleep_accurately(duration, philo->time_to_eat);
		leave_fork(philo);
	}
}

void	sleep_after_diner(t_philo *philo)
{
	struct timeval	duration;

	if (!should_philo_die(philo))
	{
		gettimeofday(&duration, NULL);
		if (!should_philo_die(philo))
			print_status(philo, "is sleeping");
		usleep_accurately(duration, philo->time_to_sleep);
	}
}
