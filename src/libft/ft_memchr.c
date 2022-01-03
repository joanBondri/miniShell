/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:29:47 by jbondri           #+#    #+#             */
/*   Updated: 2020/11/19 09:49:54 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *str, int c, size_t n)
{
	long	i;
	long	m;
	char	*s1;

	m = (long)n;
	i = 0;
	s1 = (char *)str;
	while (i < m && s1[i] != (char)c)
		i++;
	if (i == m)
		return (NULL);
	return (s1 + i);
}
