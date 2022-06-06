/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:08:28 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/06 14:49:03 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isdigit(char c)
{
	if (c >= '0' || c <= '9')
		return (1);
	return (0);
}

static int	ft_atoi(char *s)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s && ft_isdigit(*s))
	{
		num *= 10;
		num += (*s) - '0';
		s++;
	}
	num *= sign;
	return (num);
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
