/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:52:19 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/30 13:52:55 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *arg)
{
	int		i;

	arg = NULL;
	i = 0;
	while (1)
	{
		i++;
		sleep(2);
		if (i == 5)
		{
			printf("EXIT\n");
			exit(42);
		}
	}
	return (NULL);
}

void	philo_simulation(pid_t philo)
{
	pthread_t	moni;

	printf("philo pid >> %d\n", philo);
	pthread_create(&moni, NULL, check_death, NULL);
	while (1)
	{
		printf("eat\n");
		sleep(1);
		printf("sleep\n");
		sleep(1);
		printf("think\n");
		sleep(1);
		printf("repeat\n");
		sleep(1);
	}
}

int	main(int argc, char **argv)
{
	int		philo_num;
	pid_t	*philos;
	int		i;
	int		status;

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
			philo_simulation(philos[i]);
		i++;
	}
	sleep(15);
	status = 42;
	pid_t	end_pid;
	i = 0;
	while (i < philo_num)
	{
		printf("* ");
		end_pid = waitpid(philos[i], &status, WNOHANG);
		if (WEXITSTATUS(status) == 42)
		{
			printf("PID %d Is Done >> EXIT STATUS : %d\n", end_pid, WEXITSTATUS(status));
			break ;
		}
		usleep(500);
		i++;
		if (i == philo_num)
			i = 0;
	}
	return (0);
}
