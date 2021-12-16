/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:38:11 by jbondri           #+#    #+#             */
/*   Updated: 2021/06/11 11:11:23 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(char *destination, const char *source, size_t size)
{
	size_t		len_src;
	size_t		len_cpy;

	if (!destination || !source)
		return (0);
	len_src = ft_strlen(source);
	if (size)
	{
		if (len_src >= size)
			len_cpy = size - 1;
		else
			len_cpy = len_src;
		ft_memcpy(destination, source, len_cpy);
		destination[len_cpy] = '\0';
	}
	return (len_src);
}
