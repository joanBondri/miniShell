/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_3434.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:04:11 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/21 12:04:12 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define LIMITEMAL 5

void	*ft_malloc_3434(size_t si)
{
	static int	i = 0;

	i++;
	if (i < LIMITEMAL)
		return (malloc(si));
	return (NULL);
}
