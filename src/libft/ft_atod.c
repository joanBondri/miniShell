/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_cool_function_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:44:31 by jbondri           #+#    #+#             */
/*   Updated: 2021/06/11 10:46:26 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	decimal(char *dot_str)
{
	double	step;
	double	decimal;

	decimal = (double)ft_atoi(dot_str + 1);
	step = 1;
	while (*(++dot_str) == '0')
		step /= 10;
	if (*dot_str == '\0')
		return (0);
	while (decimal >= step)
		decimal /= 10;
	return (decimal);
}

static char	*afterset(char *source, char *set)
{
	int		i;

	i = 0;
	if (!source || !set)
		return (NULL);
	while (ft_strchr(set, source[i]) && source[i])
		i++;
	return (source + i);
}

double	ft_atod(char *str)
{
	double	res;
	char	*dot_str;
	int		sign;

	sign = 1;
	dot_str = str;
	if (*dot_str == '-' || *dot_str == '+')
	{
		if (*dot_str == '-')
			sign = -1;
		dot_str++;
	}
	res = (double)ft_atoi(dot_str);
	if (res < 0)
		return (0.0);
	dot_str = afterset(dot_str, "0123456789");
	if (dot_str[0] != '.')
		return (sign * res);
	return (sign * (res + decimal(dot_str)));
}
