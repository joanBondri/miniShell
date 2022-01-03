/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:36:42 by jbondri           #+#    #+#             */
/*   Updated: 2021/06/11 11:09:08 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*res;

	i = -1;
	len = 0;
	while (s[len])
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (!(res))
		return (NULL);
	while (s[++i])
		res[i] = s[i];
	res[len] = '\0';
	return (res);
}
