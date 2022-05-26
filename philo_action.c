/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:06:41 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/26 11:16:52 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grep_forks(t_philo *philo)
{
	int		right_fork;
	int		left_fork;
	int		ret;

	ret = check_death_flag(philo->info);
	if (!ret)
	{
		decide_fork_priority(philo, &right_fork, &left_fork);
		pthread_mutex_lock(&(philo->info->forks[right_fork]));
		pthread_mutex_lock(&(philo->info->forks[left_fork]));
	}
	return (ret);
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
	int				ret;

	ret = check_death_flag(philo->info);
	if (ret)
		leave_forks(philo);
	else
	{
		gettimeofday(&duration, NULL);
		gettimeofday(philo->last_meal, NULL);
		if (!check_death_flag(philo->info))
			print_statement(philo, "is eating");
		(philo->eat_count)--;
		usleep((philo->args->time_to_eat * 900));
		while (1)
		{
			if ((int)make_timestamp(&duration) >= philo->args->time_to_eat)
				break ;
		}
	}
	return (ret);
}

int	sleep_after_diner(t_philo *philo)
{
	struct timeval	duration;
	int				ret;

	ret = check_death_flag(philo->info);
	if (!ret)
	{
		gettimeofday(&duration, NULL);
		// if death flag is false;
		// unlock and printf;
		// else
		// lock????;
		if (!check_death_flag(philo->info))
			print_statement(philo, "is sleeping");
		usleep(philo->args->time_to_sleep * 900);
		while (1)
		{
			if ((int)make_timestamp(&duration) >= philo->args->time_to_sleep)
				break ;
		}
	}
	return (ret);
}
