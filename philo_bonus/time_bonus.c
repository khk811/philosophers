/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:48:17 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/06 14:48:18 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_milisecond(int sec, int usec)
{
	return ((sec * 1000) + (usec / 1000));
}

size_t	make_timestamp(struct timeval start)
{
	struct timeval	curr;
	size_t			curr_time;
	size_t			start_time;

	gettimeofday(&curr, NULL);
	curr_time = get_milisecond(curr.tv_sec, curr.tv_usec);
	start_time = get_milisecond(start.tv_sec, start.tv_usec);
	return (curr_time - start_time);
}

void	usleep_accurately(struct timeval stamp, int usleep_duration)
{
	usleep(usleep_duration * 900);
	while (1)
	{
		if ((int)make_timestamp(stamp) >= usleep_duration)
			break ;
		usleep(150);
	}
}
