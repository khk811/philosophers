/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pid_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:51:34 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/06 14:52:45 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_exit_status(int status)
{
	return ((status >> 8) & (0x000000ff));
}

void	kill_philos(pid_t *philos_pid, int philo_num, int dead_pid)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (dead_pid != (int)(philos_pid[i]))
			kill(philos_pid[i], SIGKILL);
		i++;
	}
}
