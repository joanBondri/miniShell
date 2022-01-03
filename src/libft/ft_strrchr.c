/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:40:38 by jbondri           #+#    #+#             */
/*   Updated: 2020/11/18 16:46:44 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	int		len;

	len = 0;
	s = (char *)str;
	while (str[len])
		len++;
	while (len >= 0)
	{
		if (str[len] == c)
			return (s + len);
		len--;
	}
	return (NULL);
}
