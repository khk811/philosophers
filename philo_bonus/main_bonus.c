/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:52:19 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 20:23:41 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_simulation(t_philo philo)
{
	pthread_t	moni;

	pthread_create(&moni, NULL, check_death, &philo);
	while (1)
	{
		eat_spaghetti(&philo);
		if (philo.num_of_must_eat == 0)
			exit(24);
		sleep_after_diner(&philo);
		// philo_simulate args -> *philo or philo?
		if (!should_philo_die(&philo))
			print_statement(&philo, "is thinking");
		usleep(150);
	}
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	pid_t	*philos_pid;
	int		i;
	int		j;
	int		status;
	int		full_philo;

	parse_input(&philo, argc, argv);
	philos_pid = malloc(sizeof(pid_t) * philo.philo_num);
	if (!philos_pid)
		return (1);
	t_philo_init(&philo);
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
			// break -> kill 0 to i;
		}
		else if (philos_pid[i] == 0)
		{
			philo.id = i;
			philo_simulation(philo);
		}
		i++;
	}
	status = 42;
	i = 0;
	full_philo = 0;
	while (i < philo.philo_num)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 42)
		{
			j = 0;
			while (j < philo.philo_num)
			{
				if (i != j)
					kill(philos_pid[j], SIGKILL);
				j++;
			}
			printf("send kill sig to all\n");
			break ;
		}
		if (WEXITSTATUS(status) == 24)
			full_philo++;
		usleep(150);
		i++;
	}
	if (full_philo == philo.philo_num)
		printf("All philo ate well. The end\n");
	free(philos_pid);
	// sem_close;
	return (0);
}
