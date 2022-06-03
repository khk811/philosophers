/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:20:17 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 18:40:11 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_philo_die(t_philo *philo)
{
	int	starve_time;

	starve_time = (int)make_timestamp(philo->last_meal);
	if (philo->args->time_to_die <= starve_time)
	{
		pthread_mutex_lock(&(philo->info->death));
		philo->info->death_flag = 1;
		pthread_mutex_unlock(&(philo->info->death));
		usleep(100);
		pthread_mutex_lock(&(philo->info->print));
		printf("%zu %d died\n", make_timestamp(philo->info->start), philo->id);
		pthread_mutex_unlock(&(philo->info->print));
	}
	return (philo->info->death_flag);
}

int	is_philo_full(t_philo *philo)
{
	if (philo->eat_count == 0)
	{
		pthread_mutex_lock(&(philo->info->full));
		(philo->info->hungry_philo)--;
		pthread_mutex_unlock(&(philo->info->full));
		return (1);
	}
	return (0);
}

void	print_status(t_philo *philo, char *s)
{
	pthread_mutex_lock(&(philo->info->print));
	if (!did_someone_die(philo->info))
		printf("%zu %d %s\n", make_timestamp(philo->info->start), philo->id, s);
	pthread_mutex_unlock(&(philo->info->print));
}

int	did_someone_die(t_info *info)
{
	int	ret;

	pthread_mutex_lock(&(info->death));
	ret = info->death_flag;
	pthread_mutex_unlock(&(info->death));
	return (ret);
}
