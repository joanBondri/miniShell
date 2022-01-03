/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:39:50 by jbondri           #+#    #+#             */
/*   Updated: 2021/06/11 11:13:21 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((int)(unsigned char)str1[i] - (int)(unsigned char)str2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((int)(unsigned char)str1[i] - (int)(unsigned char)str2[i]);
}
