/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:19:58 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 10:45:37 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_inset(char s, char const *set)
{
	int	m;

	m = 0;
	while (set[m])
	{
		if (set[m] == s)
			return (1);
		m++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		m;
	int		k;
	int		i;

	if (s1 == 0)
		return (0);
	i = 0;
	m = 0;
	while (s1[m] && ft_is_inset(s1[m], set))
		m++;
	k = ft_strlen(s1);
	while (k > m && ft_is_inset(s1[k - 1], set))
		k--;
	s2 = malloc(sizeof(char) * (k - m + 1));
	if (!(s2))
		return (NULL);
	while (m < k)
		s2[i++] = s1[m++];
	s2[i] = 0;
	return (s2);
}
