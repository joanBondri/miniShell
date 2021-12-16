/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:39:31 by jbondri           #+#    #+#             */
/*   Updated: 2021/06/11 11:13:00 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*res;

	if (s == NULL || f == NULL)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!(res))
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s))
		res[i] = (*f)(i, s[i]);
	res[i] = '\0';
	return (res);
}
