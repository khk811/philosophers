/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:48:07 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/06 15:46:47 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo	*philo, char *s)
{
	sem_wait(philo->print);
	if (!should_philo_die(philo))
		printf("%zu %d %s\n", make_timestamp(philo->start), philo->id, s);
	sem_post(philo->print);
}

void	*check_death(void *void_philo)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)(void_philo);
	i = 0;
	while (1)
	{
		if (should_philo_die(philo))
		{
			printf("%zu %d died\n", make_timestamp(philo->start), philo->id);
			exit(42);
		}
		usleep(150);
	}
	return (NULL);
}

int	should_philo_die(t_philo *philo)
{
	if ((int)make_timestamp(philo->last_meal) >= philo->time_to_die)
		return (1);
	return (0);
}
