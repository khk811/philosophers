/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:06:41 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 16:15:13 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grep_forks(t_philo *philo)
{
	int		right_fork;
	int		left_fork;
	// int		ret;

	// ret = check_death_flag(philo->info);
	decide_fork_priority(philo, &right_fork, &left_fork);
	// if (right_fork == left_fork)
	// 	return (0);
	if (check_death_flag(philo->info))
		return (0);
	else
	{
		pthread_mutex_lock(&(philo->info->forks[right_fork]));
		philo->info->fork_arr[right_fork] = 0;
		print_statement(philo, "has taken a fork");
		if (right_fork == left_fork)
		{
			usleep_accurately(&(philo->last_meal), philo->args->time_to_die);
			usleep(1000);
			// usleep(philo->args->time_to_die * 900);
			// while (1)
			// {
			// 	if ((int)make_timestamp(philo->last_meal) >= philo->args->time_to_die)
			// 		break ;
			// 	usleep(150);
			// }
			pthread_mutex_unlock(&(philo->info->forks[right_fork]));
			return (0);
		}
		pthread_mutex_lock(&(philo->info->forks[left_fork]));
		philo->info->fork_arr[left_fork] = 0;
		print_statement(philo, "has taken a fork");
		return (1);
	}
}

void	leave_forks(t_philo *philo)
{
	int		right_fork;
	int		left_fork;

	decide_fork_priority(philo, &right_fork, &left_fork);
	philo->info->fork_arr[left_fork] = 1;
	pthread_mutex_unlock(&(philo->info->forks[left_fork]));
	philo->info->fork_arr[right_fork] = 1;
	pthread_mutex_unlock(&(philo->info->forks[right_fork]));
}

int	eat_spaghetti(t_philo *philo)
{
	struct timeval	duration;
	// int				ret;

	// ret = check_death_flag(philo->info);
	// if (ret)
	// 	leave_forks(philo);
	// else
	if (!check_death_flag(philo->info))
	{
		if (!grep_forks(philo))
			return (check_death_flag(philo->info));
		gettimeofday(&duration, NULL);
		gettimeofday(&(philo->last_meal), NULL);
		if (!check_death_flag(philo->info))
			print_statement(philo, "is eating");
		(philo->eat_count)--;
		usleep_accurately(&duration, philo->args->time_to_eat);
		// usleep((philo->args->time_to_eat * 900));
		// while (1)
		// {
		// 	if ((int)make_timestamp(&duration) >= philo->args->time_to_eat)
		// 		break ;
		// 	usleep(150);
		// }
		leave_forks(philo);
	}
	return (check_death_flag(philo->info));
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
		usleep_accurately(&duration, philo->args->time_to_sleep);
		// usleep(philo->args->time_to_sleep * 900);
		// while (1)
		// {
		// 	if ((int)make_timestamp(&duration) >= philo->args->time_to_sleep)
		// 		break ;
		// 	usleep(150);
		// }
	}
	return (ret);
}
