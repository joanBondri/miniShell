/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:06:36 by xchalle           #+#    #+#             */
/*   Updated: 2022/01/21 15:48:32 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		k;
	char	*str;
	int		l;
	int		m;

	i = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	l = ft_strlen(s1);
	m = ft_strlen(s2);
	str = malloc(sizeof(char) * (l + m) + 1);
	if (!(str))
		return (0);
	while (s1[i])
		str[k++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		str[k] = s2[i];
		k++;
		i++;
	}
	str[k] = '\0';
	return (str);
}
