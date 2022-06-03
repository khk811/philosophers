/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:06:41 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 19:51:54 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_fork_index(t_philo *philo, int *right, int *left)
{
	int	id;
	int	num;

	id = philo->id;
	num = philo->args->philo_num;
	*right = id;
	*left = ((num - 1) + id) % num;
}

int	grab_forks(t_philo *philo)
{
	int		right_fork;
	int		left_fork;

	get_fork_index(philo, &right_fork, &left_fork);
	if (did_someone_die(philo->info))
		return (0);
	else
	{
		pthread_mutex_lock(&(philo->info->forks[right_fork]));
		philo->info->fork_arr[right_fork] = 0;
		print_status(philo, "has taken a fork");
		if (right_fork == left_fork)
		{
			usleep_accurately((philo->last_meal), philo->args->time_to_die);
			usleep(1000);
			pthread_mutex_unlock(&(philo->info->forks[right_fork]));
			return (0);
		}
		pthread_mutex_lock(&(philo->info->forks[left_fork]));
		philo->info->fork_arr[left_fork] = 0;
		print_status(philo, "has taken a fork");
		return (1);
	}
}

void	leave_forks(t_philo *philo)
{
	int		right_fork;
	int		left_fork;

	get_fork_index(philo, &right_fork, &left_fork);
	philo->info->fork_arr[left_fork] = 1;
	pthread_mutex_unlock(&(philo->info->forks[left_fork]));
	philo->info->fork_arr[right_fork] = 1;
	pthread_mutex_unlock(&(philo->info->forks[right_fork]));
}

int	eat_spaghetti(t_philo *philo)
{
	struct timeval	duration;

	if (!did_someone_die(philo->info))
	{
		if (!grab_forks(philo))
			return (did_someone_die(philo->info));
		gettimeofday(&duration, NULL);
		gettimeofday(&(philo->last_meal), NULL);
		if (!did_someone_die(philo->info))
			print_status(philo, "is eating");
		pthread_mutex_lock(&(philo->info->full));
		(philo->eat_count)--;
		pthread_mutex_unlock(&(philo->info->full));
		usleep_accurately(duration, philo->args->time_to_eat);
		leave_forks(philo);
	}
	return (did_someone_die(philo->info));
}

int	sleep_after_diner(t_philo *philo)
{
	struct timeval	duration;
	int				ret;

	ret = did_someone_die(philo->info);
	if (!ret)
	{
		gettimeofday(&duration, NULL);
		if (!did_someone_die(philo->info))
			print_status(philo, "is sleeping");
		usleep_accurately(duration, philo->args->time_to_sleep);
	}
	return (ret);
}
