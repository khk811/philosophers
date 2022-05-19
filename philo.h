/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:55:05 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/19 16:06:25 by hyunkkim         ###   ########seoul.kr  */
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
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_must_eat;
}	t_args;

typedef struct s_info
{
	// general infos;
	struct timeval	*start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	// int fork_something arr idk;
}	t_info;

typedef struct s_philo
{
	int	id;
	int	eat_count;
	int	death;
	t_info	*info;
	t_args	*args;
	pthread_t	philo;
}	t_philo;

t_args	*t_args_init(void);
t_info	*t_info_init(t_args *args);
t_philo	*t_philo_init(t_info *info, t_args *args);
t_philo	*philo_on_the_table(t_args *args, t_info *info);
void	*take_forks(void *philo);
int		ft_atoi(char *s);

#endif
