/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:06:41 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/23 13:11:05 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grep_forks(t_philo *philo)
{
	int		right_fork;
	int		left_fork;

	if (!should_philo_die(philo))
	{
		decide_fork_priority(philo, &right_fork, &left_fork);
		pthread_mutex_lock(&(philo->info->forks[right_fork]));
		pthread_mutex_lock(&(philo->info->forks[left_fork]));
	}
	return (philo->is_dead);;
}

void	leave_forks(t_philo *philo)
{
	int		right_fork;
	int		left_fork;

	decide_fork_priority(philo, &right_fork, &left_fork);
	pthread_mutex_unlock(&(philo->info->forks[left_fork]));
	pthread_mutex_unlock(&(philo->info->forks[right_fork]));
}

int	eat_spaghetti(t_philo *philo)
{
	struct timeval	duration;

	if (should_philo_die(philo))
		leave_forks(philo);
	else
	{
		gettimeofday(&duration, NULL);
		gettimeofday(philo->last_meal, NULL);
		print_statement(philo, "is eating");
		usleep((philo->args->time_to_eat * 900));
		while (1)
		{
			if ((int)make_timestamp(&duration) >= philo->args->time_to_eat)
				break ;
		}
	}
	return (philo->is_dead);
}

int	sleep_after_diner(t_philo *philo)
{
	struct timeval	duration;

	if (!should_philo_die(philo))
	{
		gettimeofday(&duration, NULL);
		print_statement(philo, "is sleeping");
		usleep(philo->args->time_to_sleep * 900);
		while (1)
		{
			if ((int)make_timestamp(&duration) >= philo->args->time_to_sleep)
				break ;
		}
	}
	return (philo->is_dead);
}
