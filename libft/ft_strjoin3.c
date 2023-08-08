/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:14:21 by xchalle           #+#    #+#             */
/*   Updated: 2022/01/16 11:39:45 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*tmp2;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (tmp == NULL)
		return (NULL);
	tmp2 = ft_strjoin(tmp, s3);
	free(tmp);
	if (tmp2 == NULL)
		return (NULL);
	return (tmp2);
}
