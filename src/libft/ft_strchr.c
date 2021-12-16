/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:36:20 by jbondri           #+#    #+#             */
/*   Updated: 2021/06/11 11:08:39 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*s;

	i = -1;
	s = (char *)str;
	while (str[++i])
	{
		if (str[i] == c)
			return (s + i);
	}
	if (c == 0 && s[i] == '\0')
		return (s + i);
	return (NULL);
}

char	*ft_loop_strchr_or(const char *str, char *c)
{
	char	*res;
	int		i;

	i = -1;
	if (!str || !c)
		return (NULL);
	while (c[++i])
	{
		res = ft_strchr(str, c[i]);
		if (res != NULL)
			break ;
	}
	return (res);
}

char	*ft_loop_strchr(const char *str, char *c)
{
	char	*res;
	int		i;

	i = -1;
	if (!str || !c)
		return (NULL);
	while (c[++i])
	{
		res = ft_strchr(str, c[i]);
		if (res == NULL)
			break ;
	}
	return (res);
}
