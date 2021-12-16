/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:35:20 by jbondri           #+#    #+#             */
/*   Updated: 2020/11/18 16:35:22 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	if (s == NULL)
		return ;
	i = -1;
	while (s[++i])
		ft_putchar_fd(s[i], fd);
	return ;
}
