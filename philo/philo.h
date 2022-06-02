/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:55:05 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/02 16:25:57 by hyunkkim         ###   ########seoul.kr  */
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
	struct timeval	*start;
	pthread_mutex_t	*forks;
	int				*fork_arr;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	int				death_flag;
	pthread_mutex_t	start_line;
	pthread_mutex_t full;
	int				hungry_philo;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	struct timeval	*last_meal;
	int				is_dead;
	t_info			*info;
	t_args			*args;
	pthread_t		philo;
}	t_philo;

t_args	*t_args_init(void);
t_info	*t_info_init(t_args *args);
t_philo	*philos_init(t_args *args, t_info *info);
size_t	get_milisecond(int sec, int usec);
void	*philos_simulation(void *philo);
int		should_philo_die(t_philo *philo);
void	decide_fork_priority(t_philo *philo, int *right, int *left);
size_t	make_timestamp(struct timeval *start);
int		grep_forks(t_philo *philo);
void	leave_forks(t_philo *philo);
int		eat_spaghetti(t_philo *philo);
int		sleep_after_diner(t_philo *philo);
void	print_statement(t_philo *philo, char *s);
int		ft_atoi(char *s);

// screening
int	check_death_flag(t_info *info);

#endif
