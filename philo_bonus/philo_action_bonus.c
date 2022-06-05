/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:12:09 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 13:51:02 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	grab_fork(t_philo *philo)
{
	// if philo is not dead or something;
	// if (philo->philo_num == 1)
	// 	return (0);
	if (should_philo_die(philo))
		return (0);
	else
	{
		sem_wait(philo->forks);
		print_statement(philo, "has taken a fork");
		sem_wait(philo->forks);
		print_statement(philo, "has taken a fork");
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

	// if philo isn's dead
	if (!should_philo_die(philo))
	{
		if (!grab_fork(philo))
			return ;
		gettimeofday(&duration, NULL);
		gettimeofday(philo->last_meal, NULL);
		// if philo isn't dead;
		if (!should_philo_die(philo))
			print_statement(philo, "is eating");
		(philo->num_of_must_eat)--;
		usleep(philo->time_to_eat * 900);
		while (1)
		{
			if ((int)make_timestamp(&duration) >= philo->time_to_eat)
				break ;
			usleep(150);
		}
		leave_fork(philo);
	}
}

void	sleep_after_diner(t_philo *philo)
{
	struct timeval	duration;

	// if philo isn't dead
	if (!should_philo_die(philo))
	{
		gettimeofday(&duration, NULL);
		// if philo isn't dead
		if (!should_philo_die(philo))
			print_statement(philo, "is sleeping");
		usleep(philo->time_to_sleep * 900);
		while (1)
		{
			if ((int)make_timestamp(&duration) >= philo->time_to_sleep)
				break ;
			usleep(150);
		}
	}
}
