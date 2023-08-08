/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:52:24 by xchalle           #+#    #+#             */
/*   Updated: 2020/11/22 15:47:37 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (s == 0)
		return (0);
	if (d < s)
	{
		while (i < len)
			d[i++] = *s++;
	}
	else
	{
		while (i < len)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	return (dest);
}
