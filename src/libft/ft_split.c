/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:36:02 by jbondri           #+#    #+#             */
/*   Updated: 2021/09/06 17:59:43 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static char	**first_alloc(char *s, char *c)
{
	int		i;
	int		count;
	char	**tab;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_strchr(c, s[i]))
			i++;
		if (!s[i])
			break ;
		while (s[i] && !ft_strchr(c, s[i]))
			i++;
		count++;
	}
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tab[count] = NULL;
	return (tab);
}

static char	**second_alloc(char **tab, char *s, char *c)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	j = -1;
	while (s[i])
	{
		count = 0;
		while (s[i] && ft_strchr(c, s[i]))
			i++;
		if (!s[i])
			break ;
		while (s[i] && !ft_strchr(c, s[i]))
		{
			i++;
			count++;
		}
		tab[++j] = malloc(sizeof(char) * (count + 1));
		if (!tab[j])
			return (NULL);
	}
	return (tab);
}

static char	**fill_tab(char **tab, char *s, char *c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	while (s[i])
	{
		j++;
		k = -1;
		while (s[i] && ft_strchr(c, s[i]))
			i++;
		if (!s[i])
			break ;
		while (s[i] && !ft_strchr(c, s[i]))
			tab[j][++k] = s[i++];
		tab[j][++k] = '\0';
	}
	return (tab);
}

char	**ft_split(char const *s, char *c)
{
	char	*str;
	char	**tab;

	if (s == NULL || c == NULL)
		return (NULL);
	str = (char *)s;
	tab = first_alloc(str, c);
	if (!(tab))
		return (NULL);
	if (!(second_alloc(tab, str, c)))
		return (NULL);
	fill_tab(tab, str, c);
	return (tab);
}

void	free_tab(char **s)
{
	int		i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}
