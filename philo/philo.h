/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:55:05 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 19:52:00 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_args
{
	int		philo_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	size_t	num_of_must_eat;
}	t_args;

typedef struct s_info
{
	struct timeval	start;
	pthread_mutex_t	*forks;
	int				*fork_arr;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	int				death_flag;
	pthread_mutex_t	start_line;
	pthread_mutex_t	full;
	int				hungry_philo;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	struct timeval	last_meal;
	int				is_dead;
	t_info			*info;
	t_args			*args;
	pthread_t		philo;
}	t_philo;

// main.c
void	*feed_philos(void *philo);

// parse.c
int		parse_input(t_args *args, int argc, char **argv);

// struct_alloc.c
int		free_t_info(t_info *info, t_args *args);
int		free_info_n_philos(t_info *info, t_philo **philos, t_args *args);
int		alloc_info_n_philos(t_info *info, t_philo **philos, t_args *args);

//struct_init.c
int		t_info_init(t_info *info, t_args *args);
int		philos_init(t_args *args, t_info *info, t_philo *philos);

// philos_status.c
int		should_philo_die(t_philo *philo);
int		did_someone_die(t_info *info);
int		is_philo_full(t_philo *philo);
void	print_status(t_philo *philo, char *s);

// philos_action.c
int		grab_forks(t_philo *philo);
void	leave_forks(t_philo *philo);
int		eat_spaghetti(t_philo *philo);
int		sleep_after_diner(t_philo *philo);

// time.c
size_t	get_milisecond(int sec, int usec);
size_t	make_timestamp(struct timeval start);
void	usleep_accurately(struct timeval stamp, int usleep_duration);

#endif
