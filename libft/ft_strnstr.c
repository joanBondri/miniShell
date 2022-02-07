/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:04:04 by xchalle           #+#    #+#             */
/*   Updated: 2020/11/21 18:17:09 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		m;
	char	*h;

	h = (char *)haystack;
	i = 0;
	if (needle[0] == '\0')
		return (h);
	while (h[i] && i < len)
	{
		m = 0;
		while (h[i + m] == needle[m] && (i + m) < len)
		{
			if (needle[m + 1] == '\0')
				return (&h[i]);
			m++;
		}
		i++;
	}
	return (0);
}
