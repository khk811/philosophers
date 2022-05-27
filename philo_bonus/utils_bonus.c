/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:08:28 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/05/27 12:08:54 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isdigit(char c)
{
	if (c >= '0' || c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *s)
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
	while(*s && ft_isdigit(*s))
	{
		num *= 10;
		num += (*s) - '0';
		s++;
	}
	num *= sign;
	return (num);
}
