/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:04:19 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/06 15:41:15 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_is_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
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
	if (!ft_is_number(s))
		return (-1);
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
		args->philo_num = ft_atoi(argv[1]);
		args->time_to_die = ft_atoi(argv[2]);
		args->time_to_eat = ft_atoi(argv[3]);
		args->time_to_sleep = ft_atoi(argv[4]);
		args->num_of_must_eat = -1;
		if (argc == 6 && ft_atoi(argv[5]) > 0)
			args->num_of_must_eat = ft_atoi(argv[5]);
		else if (argc == 6 && ft_atoi(argv[5]) <= 0)
			return (0);
	}
	if (args->philo_num < 1 || args->time_to_die < 1 || \
	args->time_to_eat < 1 || args->time_to_sleep < 1)
		return (0);
	return (1);
}
