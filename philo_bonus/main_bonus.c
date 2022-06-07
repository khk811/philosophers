/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:52:19 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/07 11:36:30 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	feed_philos(t_philo *philo)
{
	pthread_t	moni;

	if (pthread_create(&moni, NULL, check_death, (void *)philo) != 0)
		exit(42);
	while (1)
	{
		eat_spaghetti(philo);
		if (philo->num_of_must_eat == 0)
			exit(24);
		sleep_after_diner(philo);
		if (!should_philo_die(philo))
			print_status(philo, "is thinking");
		usleep(150);
	}
}

int	create_philos(t_philo *philo, pid_t *philos_pid)
{
	int	i;

	i = 0;
	while (i < philo->philo_num)
	{
		philos_pid[i] = fork();
		if (philos_pid[i] < 0)
		{
			kill_philos(philos_pid, i, -1);
			return (0);
		}
		else if (philos_pid[i] == 0)
		{
			philo->id = i;
			feed_philos(philo);
		}
		i++;
	}
	return (1);
}

void	check_philos(pid_t *philos_pid, t_philo *philo)
{
	int	status;
	int	i;
	int	full_philo;
	int	dead_philo;

	status = 0;
	i = 0;
	full_philo = 0;
	while (i < philo->philo_num)
	{
		dead_philo = waitpid(-1, &status, 0);
		if (get_exit_status(status) == 42)
		{
			kill_philos(philos_pid, philo->philo_num, dead_philo);
			return ;
		}
		if (get_exit_status(status) == 24)
			full_philo++;
		i++;
	}
	if (full_philo == philo->philo_num)
		printf("All philosophers ate well. The end\n");
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	pid_t	*philos_pid;

	if (!parse_input(&philo, argc, argv))
		return (1);
	philos_pid = malloc(sizeof(pid_t) * philo.philo_num);
	if (!philos_pid)
		return (1);
	if (!t_philo_init(&philo))
	{
		free(philos_pid);
		return (1);
	}
	if (!create_philos(&philo, philos_pid))
	{
		free(philos_pid);
		return (1);
	}
	check_philos(philos_pid, &philo);
	free(philos_pid);
	sem_close(philo.forks);
	sem_close(philo.print);
	return (0);
}
