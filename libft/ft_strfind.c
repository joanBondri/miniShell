/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:05:21 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/21 12:05:29 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strfind(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!str)
		return (-1);
	while (str[len])
		len++;
	while (str[i] && str[i] != c)
		i++;
	if (i != len)
		return (i);
	else
		return (-1);
}
