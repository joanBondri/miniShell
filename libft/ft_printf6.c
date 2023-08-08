/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:59:22 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 10:54:16 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printer_str(t_flag list, char *s)
{
	int	i;
	int	max;
	int	compt;

	compt = 0;
	i = 0;
	max = ft_strlen(s);
	if ((size_t)list.second < ft_strlen(s))
		max = list.second;
	while (list.first > max)
	{
		compt = compt + ft_putchar_fd_returnvalue(list.padding, 1);
		list.first--;
	}
	while (s[i] && i < list.second)
	{
		compt = compt + ft_putchar_fd_returnvalue(s[i], 1);
		i++;
	}
	return (compt);
}

int	ft_printer_adr2(char *u, t_flag *list, int *max, unsigned long long nbr)
{
	int	compt;

	compt = 0;
	if (ft_strlen(u) < (size_t)list->second || (list->second == 0 && nbr == 0))
		*max = list->second;
	if (list->c == 'p')
		list->first -= 2;
	if (list->c == 'p' && list->padding == '0')
		compt = compt + ft_putstr_fd_returnvalue("0x", 1, 2);
	while (list->first > *max)
	{
		compt = compt + ft_putchar_fd_returnvalue(list->padding, 1);
		list->first--;
	}
	if (list->c == 'p' && list->padding == ' ')
		compt = compt + ft_putstr_fd_returnvalue("0x", 1, 2);
	return (compt);
}

int	ft_printer_adr(t_flag list, char *u, unsigned long long nbr)
{
	int	compt;
	int	second;
	int	max;

	max = ft_strlen(u);
	second = list.second;
	compt = ft_printer_adr2(u, &list, &max, nbr);
	while ((size_t)list.second > ft_strlen(u))
	{
		compt = compt + ft_putchar_fd_returnvalue('0', 1);
		list.second--;
	}
	if ((second != 0 || (nbr != 0 && second == 0)))
		compt = compt + ft_putstr_fd_returnvalue(u, 1, ft_strlen(u));
	return (compt);
}

int	ft_printer_nbr2(long long *u, t_flag *list, int *max, int *i)
{
	int	compt;

	compt = 0;
	*i = list->second;
	*max = ft_nbrlen(*u);
	if (list->second > ft_nbrlen_unsigned(*u) || (list->second == 0 && *u == 0))
		*max = list->second;
	if (*u < 0 && ft_nbrlen_unsigned(*u) < list->second)
		*max = ft_second(*max, *u);
	while (list->first > *max)
	{
		if (*u < 0 && list->padding == '0')
		{
			compt = compt + ft_putchar_fd_returnvalue('-', 1);
			*u *= -1;
			list->second--;
		}
		compt = compt + ft_putchar_fd_returnvalue(list->padding, 1);
		list->first--;
	}
	return (compt);
}

int	ft_printer_nbr(t_flag list, long long u)
{
	int	i;
	int	compt;
	int	max;

	compt = ft_printer_nbr2(&u, &list, &max, &i);
	while (list.second > ft_nbrlen_unsigned(u))
	{
		if (u < 0 && list.c != 'u')
		{
			u *= -1;
			compt = compt + ft_putchar_fd_returnvalue('-', 1);
		}
		compt = compt + ft_putchar_fd_returnvalue('0', 1);
		list.second--;
	}
	if (i != 0 || (i == 0 && u != 0))
	{
		ft_putnbr_fd_returnvalue(u, 1);
		return (compt + ft_nbrlen(u));
	}
	return (compt);
}
