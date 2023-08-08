/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendlre_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:03:23 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/21 12:03:24 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendlre_fd(char *s, int fd, int ret)
{
	char	*tmp;

	tmp = ft_strjoin(s, "\n");
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
	return (ret);
}
