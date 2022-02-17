/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:35:31 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/17 00:14:52 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

static char	**first_alloc(char *s, char *c,
		bool (check)(char *s, int i, char *c))
{
	int		i;
	int		count;
	char	**tab;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && check(s, i, c))
			i++;
		if (!s[i])
			break ;
		while (s[i] && !check(s, i, c))
			i++;
		count++;
	}
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tab[count] = NULL;
	return (tab);
}

static char	**second_alloc(char **tab, char *s, char *c,
		bool (check)(char *s, int i, char *c))
{
	int		i;
	int		j;
	int		count;

	i = 0;
	j = -1;
	while (s[i])
	{
		count = 0;
		while (s[i] && check(s, i, c))
			i++;
		if (!s[i])
			break ;
		while (s[i] && !check(s, i, c))
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

static char	**fill_tab(char **tab, char *s, char *c,
		bool (check)(char *s, int i, char *c))
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
		while (s[i] && check(s, i, c))
			i++;
		if (!s[i])
			break ;
		while (s[i] && !check(s, i, c))
			tab[j][++k] = s[i++];
		tab[j][++k] = '\0';
	}
	return (tab);
}

char	**ft_split_func(char *s, char *c, bool (check)(char *, int, char *))
{
	char	**tab;

	if (s == NULL || c == NULL)
		return (NULL);
	tab = first_alloc(s, c, check);
	if (!(tab))
		return (NULL);
	if (!(second_alloc(tab, s, c, check)))
		return (NULL);
	fill_tab(tab, s, c, check);
	return (tab);
}
