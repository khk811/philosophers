/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:12:09 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/31 11:42:17 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	grab_fork(t_philo *philo)
{
	// if philo is not dead or something;
	if ((int)make_timestamp(philo->last_meal) < philo->time_to_die)
	{
		sem_wait(philo->forks);
		sem_wait(philo->forks);
		printf("%zu %d has taken a fork\n", make_timestamp(philo->start), philo->id);
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

	// if philo isn's dead
	if ((int)make_timestamp(philo->last_meal) < philo->time_to_die)
	{
		gettimeofday(&duration, NULL);
		gettimeofday(philo->last_meal, NULL);
		// if philo isn't dead;
		if ((int)make_timestamp(philo->last_meal) < philo->time_to_die)
			printf("%zu %d is eating\n", make_timestamp(philo->start), philo->id);
		(philo->num_of_must_eat)--;
		usleep(philo->time_to_eat * 900);
		while (1)
		{
			if ((int)make_timestamp(&duration) >= philo->time_to_eat)
				break ;
			usleep(150);
		}
	}
	leave_fork(philo);
}

void	sleep_after_diner(t_philo *philo)
{
	struct timeval	duration;

	// if philo isn't dead
	if ((int)make_timestamp(philo->last_meal) < philo->time_to_die)
	{
		gettimeofday(&duration, NULL);
		// if philo isn't dead
		if ((int)make_timestamp(philo->last_meal) < philo->time_to_die)
			printf("%zu %d is sleeping\n", make_timestamp(philo->start), philo->id);
		usleep(philo->time_to_sleep * 900);
		while (1)
		{
			if ((int)make_timestamp(&duration) >= philo->time_to_sleep)
				break ;
			usleep(150);
		}
	}
}
