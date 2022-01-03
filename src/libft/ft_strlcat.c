/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:37:31 by jbondri           #+#    #+#             */
/*   Updated: 2021/06/11 11:10:57 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_cpy;
	size_t	padding;
	char	*cdest;
	char	*csrc;

	cdest = dst;
	csrc = (char *)src;
	len_cpy = size;
	while (*cdest != '\0' && len_cpy-- != 0)
		cdest++;
	padding = cdest - dst;
	len_cpy = size - padding;
	if (len_cpy <= 0)
		return (padding + ft_strlen(src));
	while (*csrc != '\0')
	{
		if (len_cpy > 1)
		{
			*cdest++ = *csrc;
			len_cpy--;
		}
		csrc++;
	}
	*cdest = '\0';
	return (padding + (csrc - src));
}
