/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:08:21 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/07 15:07:07 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_in_base(char c, char *base)
{
	int		i;

	i = -1;
	while (base[++i] != '\0')
	{
		if (base[i] == c)
			return (i);
	}
	return (-1);
}

char	*ft_convert_base(unsigned long long nbr,
		char *base_from, char *base_to)
{
	int					size_nbr_base;
	char				*nbr_base_to;
	int					is_neg;
	int					i;

	if (!ft_is_base_valid(base_from) || !ft_is_base_valid(base_to))
		return (0);
	size_nbr_base = 0;
	is_neg = 0;
	if ((long long)nbr < 0)
	{
		is_neg = 1;
		nbr *= -1;
	}
	ft_size_nbr_base(nbr, base_to, &size_nbr_base);
	nbr_base_to = malloc(sizeof(char) * (size_nbr_base + 1 + is_neg));
	if (!(nbr_base_to))
		return (0);
	i = -1;
	if (is_neg == 1)
		nbr_base_to[++i] = '-';
	ft_convert_nbr_base(nbr, base_to, nbr_base_to, &i);
	nbr_base_to[++i] = '\0';
	return (nbr_base_to);
}
