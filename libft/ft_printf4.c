/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:58:46 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 12:05:46 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	mal_s(char *s, char *str)
{
	s = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(s))
		return ;
}

int	ft_afteresp_nbr(t_flag list, long long d)
{
	int	i;
	int	max;

	max = ft_nbrlen(d);
	if (list.second > ft_nbrlen_unsigned(d) || (list.second == 0 && d == 0))
		max = list.second;
	if (d < 0 && ft_nbrlen_unsigned(d) < list.second)
		max = ft_second(max, d);
	i = 0;
	if (list.first < 0)
	{
		list.first *= -1;
		while (list.first > max)
		{
			i = i + ft_putchar_fd_returnvalue(' ', 1);
			list.first--;
		}
	}
	return (i);
}

int	ft_afteresp_str(t_flag list, char *s)
{
	int	i;
	int	max;

	i = 0;
	max = list.second;
	if ((size_t)list.second > ft_strlen(s) && list.second != 0)
		max = ft_strlen(s);
	if (list.first < 0)
	{
		list.first *= -1;
		while (list.first > max)
		{
			i = i + ft_putchar_fd_returnvalue(' ', 1);
			list.first--;
		}
	}
	return (i);
}

int	ft_afteresp_adr(t_flag list, char *s, unsigned long long u)
{
	int	i;
	int	max;

	i = 0;
	max = ft_strlen(s);
	if (list.second > max || (list.second == 0 && u == 0))
		max = list.second;
	if (list.c == 'p')
		max += 2;
	if (list.first < 0)
	{
		list.first *= -1;
		while (list.first > max)
		{
			i = i + ft_putchar_fd_returnvalue(' ', 1);
			list.first--;
		}
	}
	return (i);
}

int	ft_afteresp_char(t_flag list)
{
	int	i;

	i = 0;
	if (list.first < 0)
	{
		list.first *= -1;
		while (list.first > 1)
		{
			i = i + ft_putchar_fd_returnvalue(' ', 1);
			list.first--;
		}
	}
	return (i);
}
