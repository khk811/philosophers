/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:52:19 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/27 12:19:41 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	int		philo_num;
	pid_t	*philos;
	int		i;

	if (argc != 2)
		return (0);
	philo_num = ft_atoi(argv[1]);
	philos = malloc(sizeof(pid_t) * philo_num);
	i = 0;
	while (i < philo_num)
	{
		philos[i] = fork();
		if (philos[i] < 0)
		{
			free(philos);
			philos = NULL;
			return (-1);
		}
		else if (philos[i] == 0)
		{
			printf("philo[%d] : %ld\n", i, (long)getpid());
			sleep(1);
			exit(0);
		}
		else
			printf("monitoring : %ld, philo[%d] : %ld\n", (long)getpid(), i, (long)philos[i]);
		i++;
	}
	return (0);
}
