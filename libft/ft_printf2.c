/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:58:19 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 11:06:16 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbrlen(long long nbr)
{
	int	i;

	i = 1;
	if (nbr < 0)
		i++;
	while (nbr / 10 != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

int	ft_nbrlen_unsigned(long long nbr)
{
	int	i;

	i = 1;
	while (nbr / 10 != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

int	in_charset(char c)
{
	if (c == 'd' || c == 'u' || c == 'p' || c == 'c' || c == 's'
		|| c == 'x' || c == 'X' || c == 'i' || c == '%')
		return (1);
	return (0);
}

char	*ft_determinate(const char *str)
{
	int		i;
	int		j;
	char	*keeper;

	keeper = malloc(sizeof(char) * (10));
	if (!(keeper))
		return (0);
	j = 0;
	i = 0;
	while (str[i] != '%')
		i++;
	i++;
	while ((str[i] >= '0' && str[i] <= '9')
		|| str[i] == '.' || str[i] == '-' || str[i] == '*')
		keeper[j++] = str[i++];
	if (in_charset(str[i]) == 1)
		keeper[j++] = str[i++];
	keeper[j] = '\0';
	return (keeper);
}

void	ft_separate(char *k, char *c)
{
	while (((*k <= '9' && *k >= '0')
			|| *k == '.' || *k == '-' || *k == '*') && *k)
		k++;
	*c = *k;
}
