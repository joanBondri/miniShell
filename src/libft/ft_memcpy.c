/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:30:38 by jbondri           #+#    #+#             */
/*   Updated: 2020/11/18 16:30:41 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	long	i;
	long	m;
	char	*s1;

	if (dest == NULL && src == NULL)
		return (NULL);
	m = (long)n;
	s1 = (char *)dest;
	i = -1;
	while (++i < m)
	{
		*s1 = *(char *)src;
		s1++;
		src++;
	}
	return (dest);
}
