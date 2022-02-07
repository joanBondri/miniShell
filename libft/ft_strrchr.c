/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:01:23 by xchalle           #+#    #+#             */
/*   Updated: 2022/01/17 11:38:29 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*i;

	i = (char *)s;
	while (*s != '\0')
		s++;
	while (*s != c && s != i)
		s--;
	if (*s == c)
		return ((char *)s);
	else
		return (0);
}
