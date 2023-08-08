/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:04:56 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 10:52:27 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init(t_flag *list, int *i)
{
	*i = 0;
	list->first = 0;
	list->second = 0;
	list->padding = ' ';
	list->c = 0;
}

void	ft_reset(t_flag *list)
{
	list->first = 0;
	list->second = 0;
	list->padding = ' ';
	list->c = 0;
}

int	ft_printf(const char *str, ...)
{
	int		i;
	t_flag	list;
	va_list	param;

	ft_init(&list, &i);
	va_start(param, str);
	while (*str)
	{
		if (*str == '%')
		{
			ft_separate(ft_determinate(str), &list.c);
			list.str = ft_replace(ft_determinate(str), param);
			i = i + ft_pourcent(param, list, list.str);
			str = str + ft_strlen(ft_determinate(str)) + 1;
			free(list.str);
		}
		else if (*str)
		{
			i = i + ft_putchar_fd_returnvalue(*str, 1);
			str++;
		}
		ft_reset(&list);
	}
	va_end(param);
	return (i);
}

int	ft_printer_char(t_flag list, long long u)
{
	int	compt;

	compt = 0;
	while (list.first > 1)
	{
		compt = compt + ft_putchar_fd_returnvalue(list.padding, 1);
		list.first--;
	}
	while (list.second > ft_nbrlen(u))
	{
		list.second--;
	}
	compt = compt + ft_putchar_fd_returnvalue(u, 1);
	return (compt);
}
