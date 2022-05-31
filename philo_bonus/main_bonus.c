/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:52:19 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/31 11:50:43 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_milisecond(int sec, int usec)
{
	return ((sec * 1000) + (usec / 1000));
}

size_t	make_timestamp(struct timeval *start)
{
	struct timeval	curr;
	size_t			curr_time;
	size_t			start_time;

	gettimeofday(&curr, NULL);
	curr_time = get_milisecond(curr.tv_sec, curr.tv_usec);
	start_time = get_milisecond(start->tv_sec, start->tv_usec);
	return (curr_time - start_time);
}

void	*check_death(void *void_philo)
{
	t_philo	philo;
	int		i;

	philo = *((t_philo *)(void_philo));
	i = 0;
	while (1)
	{
		if ((int)make_timestamp(philo.last_meal) >= philo.time_to_die)
		{
			printf("%zu %d died\n", make_timestamp(philo.start), philo.id);
			exit(42);
		}
		usleep(150);
	}
	return (NULL);
}

void	philo_simulation(t_philo philo)
{
	pthread_t	moni;

	pthread_create(&moni, NULL, check_death, &philo);
	while (1)
	{
		grab_fork(&philo);
		eat_spaghetti(&philo);
		if (philo.num_of_must_eat == 0)
		{
			printf("%d is full\n", philo.id);
			exit(24);
		}
		sleep_after_diner(&philo);
		if ((int)make_timestamp(philo.last_meal) < philo.time_to_die)
			printf("%zu %d is thinking\n", make_timestamp(philo.start), philo.id);
		usleep(150);
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
	int		j;
	int		status;

	parse_input(&philo, argc, argv);
	sem_unlink("forks");
	philo.forks = sem_open("forks", O_CREAT, 0644, (unsigned int)(philo.philo_num));
	printf("fork >> %p\n", philo.forks);
	philo.start = malloc(sizeof(struct timeval));
	philo.last_meal = malloc(sizeof(struct timeval));
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
			gettimeofday(philo.start, NULL);
			gettimeofday(philo.last_meal, NULL);
			philo_simulation(philo);
		}
		i++;
	}
	// sleep(15);
	status = 42;
	i = 0;
	while (i < philo.philo_num)
	{
		waitpid(philos_pid[i], &status, WNOHANG);
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
		if (WEXITSTATUS(status) == 24 && i == philo.philo_num - 1)
		{
			printf("All philo ate well. end\n");
			break ;
		}
		usleep(150);
		i++;
		if (i == philo.philo_num)
			i = 0;
	}
	return (0);
}
