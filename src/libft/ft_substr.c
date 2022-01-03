/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:42:19 by jbondri           #+#    #+#             */
/*   Updated: 2021/06/11 11:23:12 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

static char	*return_empty(void)
{
	char		*s;

	s = malloc(sizeof(char) * (1));
	if (!(s))
		return (NULL);
	s[0] = '\0';
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		len_str;
	char		*str;
	char		*res;

	len_str = 0;
	if (s == NULL)
		return (NULL);
	str = (char *)s;
	len_str = ft_strlen(str);
	if (len_str <= start || len == 0)
		return (return_empty());
	len_str = 0;
	len_str = ft_strlen(str + start);
	if (len > len_str)
		res = malloc(sizeof(char) * ((len_str) + 1));
	else
		res = malloc(sizeof(char) * ((len) + 1));
	if (!(res))
		return (NULL);
	i = -1;
	while (str[start + ++i] && i < len)
		res[i] = str[start + i];
	res[i] = '\0';
	return (res);
}
