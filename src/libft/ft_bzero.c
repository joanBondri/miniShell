/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:17:01 by jbondri           #+#    #+#             */
/*   Updated: 2021/06/11 10:48:18 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	char	*char_s;
	char	*char_buff;

	char_s = (char *)s;
	char_buff = char_s;
	while (char_buff < char_s + n)
	{
		(*char_buff) = 0;
		char_buff++;
	}
	return ;
}
