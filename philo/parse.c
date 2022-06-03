/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:04:19 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/03 20:02:58 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	parse_input(t_args *args, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		(args)->philo_num = ft_atoi(argv[1]);
		(args)->time_to_die = ft_atoi(argv[2]);
		(args)->time_to_eat = ft_atoi(argv[3]);
		(args)->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			(args)->num_of_must_eat = ft_atoi(argv[5]);
		else
			args->num_of_must_eat = -1;
	}
	if (args->philo_num < 1 || args->time_to_die < 1 || \
	args->time_to_eat < 1 || args->time_to_sleep < 1 || \
	args->num_of_must_eat == 0)
		return (0);
	else
		return (1);
}
