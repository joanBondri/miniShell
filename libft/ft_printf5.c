/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:59:02 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 10:54:51 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pourcent5(va_list param, t_flag list, char *str)
{
	int					i;
	unsigned long long	s;
	char				*stock;

	if (list.c == 'x')
	{
		s = 0;
		s = (unsigned int)va_arg(param, unsigned int);
		stock = ft_convert_base(s, "0123456789", "0123456789abcdef");
		ft_atoooi(str, &list, stock, 0);
		i = ft_printer_adr(list, stock, s) + ft_afteresp_adr(list, stock, s);
		free(stock);
	}
	if (list.c == '%')
	{
		ft_atoooi(str, &list, "%", 0);
		i = ft_printer_char(list, '%');
		i = i + ft_afteresp_char(list);
	}
	return (i);
}

int	ft_pourcent4(va_list param, t_flag list, char *str)
{
	int					i;
	char				*s;
	unsigned long long	u;
	char				*stock;

	if (list.c == 's')
	{
		s = (char *)va_arg(param, char *);
		if (s == NULL)
			s = "(null)";
		ft_atoooi(str, &list, s, 0);
		i = ft_printer_str(list, s) + ft_afteresp_str(list, s);
	}
	if (list.c == 'p')
	{
		u = (unsigned long long)va_arg(param, unsigned long long);
		stock = ft_convert_base(u, "0123456789", "0123456789abcdef");
		ft_atoooi(str, &list, stock, 0);
		i = ft_printer_adr(list, stock, u) + ft_afteresp_adr(list, stock, u);
		free(stock);
	}
	else if (list.c != 'p' && list.c != 's')
		return (ft_pourcent5(param, list, str));
	return (i);
}

int	ft_pourcent3(va_list param, t_flag list, char *str)
{
	unsigned long long	s;
	int					i;
	char				*stock;

	i = 0;
	if (list.c == 'X')
	{
		s = (unsigned int)va_arg(param, unsigned int);
		stock = ft_convert_base(s, "0123456789", "0123456789ABCDEF");
		ft_atoooi(str, &list, stock, 0);
		i = ft_printer_adr(list, stock, s) + ft_afteresp_adr(list, stock, s);
		free(stock);
	}
	else if (list.c != 'X')
		return (ft_pourcent4(param, list, str));
	return (i);
}

int	ft_pourcent2(va_list param, t_flag list, char *str)
{
	int				d;
	int				i;
	unsigned int	u;

	i = 0;
	if (list.c == 'd' || list.c == 'i')
	{
		d = (int)va_arg(param, int);
		ft_atoooi(str, &list, 0, d);
		i = ft_printer_nbr(list, d);
		i = i + ft_afteresp_nbr(list, d);
	}
	if (list.c == 'u')
	{
		u = (unsigned int)va_arg(param, unsigned int);
		ft_atoooi(str, &list, 0, u);
		i = ft_printer_nbr(list, u);
		i = i + ft_afteresp_nbr(list, u);
	}
	else if (list.c != 'd' && list.c != 'i' && list.c != 'u')
		return (ft_pourcent3(param, list, str));
	return (i);
}

int	ft_pourcent(va_list param, t_flag list, char *str)
{
	char				c;
	int					i;

	i = 0;
	if (list.c == 'c')
	{
		c = (char)va_arg(param, int);
		ft_atoooi(str, &list, NULL, 1);
		i = ft_printer_char(list, c) + ft_afteresp_char(list);
	}
	else if (list.c != 'c')
		return (ft_pourcent2(param, list, str));
	return (i);
}
