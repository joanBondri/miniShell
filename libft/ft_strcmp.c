/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:05:50 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/21 12:05:53 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;

	if (!s1 || !s2)
		return (1);
	c1 = (unsigned char)*s1;
	c2 = (unsigned char)*s2;
	while (*s1 && *s2)
	{
		if (c1 != c2)
			return (c1 - c2);
		++s1;
		++s2;
		c1 = (unsigned char)*s1;
		c2 = (unsigned char)*s2;
	}
	return (c1 - c2);
}
