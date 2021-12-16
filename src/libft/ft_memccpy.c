/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:29:30 by jbondri           #+#    #+#             */
/*   Updated: 2020/11/18 16:29:31 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	long	i;
	long	m;
	char	*s1;
	char	*s2;

	m = (long)n;
	s1 = (char *)dest;
	s2 = (char *)src;
	i = -1;
	while (++i < m && (unsigned char)s2[i] != (unsigned char)c)
		s1[i] = s2[i];
	if (i == m)
		return (NULL);
	s1[i] = s2[i];
	return (dest + i + 1);
}
