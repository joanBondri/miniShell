/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:31:34 by jbondri           #+#    #+#             */
/*   Updated: 2021/06/11 11:03:36 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *str, int c, size_t n)
{
	char	*s_buff;
	char	*char_str;

	char_str = (char *)str;
	s_buff = char_str;
	while (s_buff < char_str + n)
	{
		(*s_buff) = (unsigned int)c;
		s_buff++;
	}
	return (str);
}
