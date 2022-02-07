/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:08:59 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 11:10:00 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_sign(char *str, int sign)
{
	if (sign == 1)
		str[0] = '-';
	return (str);
}

static void	ft_deso(long *nbr, int *sign, int *len, int n)
{
	*nbr = n;
	*len = 0;
	*sign = 0;
}

static char	*ft_malade(int *sign, int *len, long *nbr, char *str)
{
	if (*nbr == -2147483648)
	{
		str = "-2147483648";
		return (str);
	}
	if (*nbr <= 0)
		*len = 1;
	if (*nbr < 0)
	{
		*sign = 1;
		*nbr = *nbr * -1;
	}
	return (str);
}

char	*ft_itoa(long long n)
{
	long		nbr;
	int			sign;
	int			len;
	char		*str;

	str = NULL;
	ft_deso(&nbr, &sign, &len, n);
	ft_malade(&sign, &len, &nbr, str);
	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (0);
	str[len--] = '\0';
	while (len >= sign)
	{
		str[len--] = nbr % 10 + 48;
		nbr = nbr / 10;
	}
	return (ft_sign(str, sign));
}
