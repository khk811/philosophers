/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:52:19 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/30 20:31:12 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *void_philo)
{
	t_philo	philo;
	int		i;

	philo = *((t_philo *)(void_philo));
	i = 0;
	while (1)
	{
		i++;
		sleep(2);
		if (i == 5)
		{
			printf("%d EXIT\n", philo.id);
			exit(42);
		}
	}
	return (NULL);
}

void	philo_simulation(t_philo philo)
{
	pthread_t	moni;

	pthread_create(&moni, NULL, check_death, &philo);
	while (1)
	{
		printf("%d eat\n", philo.id);
		sleep(1);
		printf("%d sleep\n", philo.id);
		sleep(1);
		printf("%d think\n", philo.id);
		sleep(1);
		printf("%d repeat\n", philo.id);
		sleep(1);
	}
}

void	parse_input(t_philo *philo, int argc, char **argv)
{

	if (argc == 5 || argc == 6)
	{
		philo->philo_num = ft_atoi(argv[1]);
		philo->time_to_die = ft_atoi(argv[2]);
		philo->time_to_eat = ft_atoi(argv[3]);
		philo->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philo->num_of_must_eat = ft_atoi(argv[5]);
		else
			philo->num_of_must_eat = -1;
	}
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	pid_t	*philos_pid;
	int		i;
	int		status;

	parse_input(&philo, argc, argv);
	sem_unlink("forks");
	philo.forks = sem_open("forks", O_CREAT, 0644, (unsigned int)(philo.philo_num));
	printf("fork >> %p\n", philo.forks);
	philos_pid = malloc(sizeof(pid_t) * philo.philo_num);
	printf("philo num : %d\n", philo.philo_num);
	i = 0;
	while (i < philo.philo_num)
	{
		philos_pid[i] = fork();
		if (philos_pid[i] < 0)
		{
			free(philos_pid);
			philos_pid = NULL;
			return (-1);
		}
		else if (philos_pid[i] == 0)
		{
			philo.id = i;
			gettimeofday(&philo.last_meal, NULL);
			philo_simulation(philo);
		}
		i++;
	}
	sleep(15);
	status = 42;
	i = 0;
	while (i < philo.philo_num)
	{
		waitpid(philos_pid[i], &status, WNOHANG);
		if (WEXITSTATUS(status) == 42 && i == philo.philo_num - 1)
		{
			printf("EXIT STATUS : %d\n", WEXITSTATUS(status));
			break ;
		}
		usleep(500);
		i++;
		if (i == philo.philo_num)
			i = 0;
	}
	return (0);
}
