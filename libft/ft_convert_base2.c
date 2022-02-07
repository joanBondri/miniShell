/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:08:45 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 11:12:07 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_size_nbr_base(long nb, char *base, int *size)
{
	int		base_size;

	base_size = 0;
	while (base[base_size] != '\0')
		base_size++;
	if (nb > base_size - 1)
		ft_size_nbr_base(nb / 10, base, size);
	*size += 1;
}

void	ft_convert_nbr_base(unsigned long long nbr,
		char *base, char *nbr_base_to, int *i)
{
	unsigned long long	base_size;
	unsigned long long	nb;

	nb = nbr;
	base_size = 0;
	while (base[base_size])
		base_size++;
	if (nb > base_size - 1)
		ft_convert_nbr_base(nb / base_size, base, nbr_base_to, i);
	*i += 1;
	nbr_base_to[*i] = base[nb % base_size];
}

int	ft_is_base_valid(char *base)
{
	int		i;
	int		j;

	i = 0;
	while (base[i] != '\0')
		i++;
	if (i == 0 || i == 1)
		return (0);
	i = -1;
	while (base[++i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-' || base[i] == '\t'
			|| base[i] == '\n' || base[i] == '\v'
			|| base[i] == '\f' || base[i] == '\r' || base[i] == ' ')
			return (0);
		j = -1;
		while (base[++j] != '\0')
		{
			if ((base[j] == base[i]) && j != i)
				return (0);
		}
	}
	return (1);
}
