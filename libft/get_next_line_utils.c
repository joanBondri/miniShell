/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:46:16 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 10:23:14 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_swap_gnl(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!src)
		return (NULL);
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\0')
	{
		dest[0] = 0;
		return (dest);
	}
	i++;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (dest);
}

int	ft_strlen_gnl(char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	ft_check(char *keeper, char c, int size)
{
	int	i;

	i = 0;
	while (keeper[i] && i < size)
	{
		if (keeper[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_empty_string(char *s1, char *s2, char c, int m)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	if (!s1)
	{
		str = malloc(sizeof(char) * (m + 1));
		if (!(str))
			return (NULL);
		while (s2[i] && s2[i] != c)
			str[k++] = s2[i++];
		str[k] = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2, char c)
{
	int		i;
	int		k;
	char	*str;
	int		l;
	int		m;

	if (!s2)
		return (NULL);
	i = 0;
	k = 0;
	m = ft_strlen_gnl(s2, c);
	if (!s1)
		return (ft_empty_string(s1, s2, c, m));
	l = ft_strlen_gnl(s1, c);
	str = malloc(sizeof(char) * (l + m) + 1);
	if (!(str))
		return (0);
	while (s1[i] && s1[i] != c)
		str[k++] = s1[i++];
	i = 0;
	while (s2[i] && s2[i] != c)
		str[k++] = s2[i++];
	str[k] = '\0';
	return (str);
}
