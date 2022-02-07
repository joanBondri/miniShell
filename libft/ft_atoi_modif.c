/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_modif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:46:08 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 11:13:25 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_atoi2(const char *str, t_flag *list, int *i, int c)
{
	*i = 0;
	if (str[*i] == '0' && ((ft_strchr(str, '.') == 0)
			|| (ft_strchr(str, '.') != 0 && ft_strchr(str, '-') != 0)
			|| list->c == 's' || list->c == 'c' || list->c == '%'))
	{
		list->padding = '0';
		(*i)++;
	}
	while (str[*i] == '-' || str[*i] == '+' || str[*i] == '0')
	{
		if (str[*i] == '-')
			c -= 1;
		(*i)++;
	}
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		list->first = list->first * 10 + (str[*i] - 48);
		(*i)++;
	}
	if (c < 0)
		list->first *= -1;
}

int	ft_atoi_modified(const char *str, t_flag *list)
{
	int	i;
	int	c;

	c = 0;
	ft_atoi2(str, list, &i, c);
	if (str[i] == '.')
	{
		i++;
		list->second = 0;
		c = 0;
		while (str[i] == '-')
		{
			c--;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			list->second = list->second * 10 + (str[i] - 48);
			i++;
		}
		if (c < 0)
			list->second *= -1;
	}
	return (0);
}
