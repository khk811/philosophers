/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:53:17 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/07 10:53:37 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	size_t			num_of_must_eat;
	sem_t			*forks;
	sem_t			*print;
	int				id;
	struct timeval	start;
	struct timeval	last_meal;
}	t_philo;

// parce_bonus.c
int		parse_input(t_philo *philo, int argc, char **argv);
// struct_init_bonus.c
int		t_philo_init(t_philo *philo);
// time_bonus.c
size_t	make_timestamp(struct timeval start);
void	usleep_accurately(struct timeval stamp, int usleep_duration);
// philo_status_bonus.c
void	print_status(t_philo	*philo, char *s);
void	*check_death(void *void_philo);
int		should_philo_die(t_philo *philo);
// philo_action_bonus.c
int		grab_fork(t_philo *philo);
void	leave_fork(t_philo *philo);
void	eat_spaghetti(t_philo *philo);
void	sleep_after_diner(t_philo *philo);
// utils_pid_bonus.c
int		get_exit_status(int status);
void	kill_philos(pid_t *philos_pid, int philo_num, int dead_pid);

#endif
