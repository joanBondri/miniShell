/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:26:05 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 12:14:55 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_find_point(char *str)
{
	if (str[0] == '*')
		return (0);
	return (1);
}

int	ft_second(int second, long long u)
{
	if (u < 0)
		second++;
	return (second);
}

void	ft_atoooi(char *s, t_flag *list, char *str, long long nbr)
{
	int	i;

	i = 0;
	while (s[i] && in_charset(s[i]) == 0)
		i++;
	if (list->c == 'd' || list->c == 'i' || list->c == 'u' || list->c == 'c')
	{
		list->first = 0;
		list->second = ft_nbrlen_unsigned(nbr);
		ft_atoi_modified(s, list);
		if (list->second < 0)
			list->second = ft_nbrlen_unsigned(nbr);
	}
	else if (list->c == 'X' || list->c == 'x'
		|| list->c == 's' || list->c == 'p' || list->c == '%')
	{
		list->first = 0;
		list->second = ft_strlen(str);
		ft_atoi_modified(s, list);
		if (list->second < 0)
			list->second = ft_strlen(str);
	}
}

void	ft_replace_summons(char *str, int *o, int *j, int *i)
{
	*o = ft_find_point(str);
	*j = 0;
	*i = 0;
}

char	*ft_replace(char *str, va_list param)
{
	int		i;
	int		j;
	char	*s;
	char	*t;
	int		o;

	ft_replace_summons(str, &o, &j, &i);
	s = NULL;
	mal_s(s, str);
	while (str[i])
	{
		if (str[i] == '*')
		{
			t = s;
			s = ft_strjoin_modif(str, s, ft_itoa((int)va_arg(param, int)), &o);
			free(t);
			while (s[j])
				j++;
			if ((size_t)i < ft_strlen(str))
				i++;
		}
		s[j++] = str[i++];
		s[j] = '\0';
	}
	return (s);
}
