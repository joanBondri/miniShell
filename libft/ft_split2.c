/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:08:05 by xchalle           #+#    #+#             */
/*   Updated: 2022/01/16 11:40:02 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free2(char **tab, int o)
{
	int	i;

	i = 0;
	while (i < o)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**ft_malloc2(char **tab, const char *str, int compteur, char c)
{
	int		k;
	int		o;
	int		i;

	i = 0;
	k = 0;
	o = 0;
	while (str[i] && o < compteur)
	{
		while (str[i] == c && str[i])
			i++;
		k = 0;
		while (str[i] != c && str[i])
		{
			tab[o][k] = str[i];
			i++;
			k++;
		}
		tab[o][k] = '\0';
		o++;
	}
	tab[o] = 0;
	return (tab);
}

static char	**ft_malloc_string2(
		char **tab, const char *str, int compteur, char c)
{
	int		k;
	int		o;
	int		i;

	i = 0;
	k = 0;
	o = 0;
	while (str[i] && o < compteur)
	{
		k = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			i++;
			k++;
		}
		tab[o] = malloc(sizeof(char) * (k + 1));
		if (!(tab[o]))
			return (ft_free2(tab, o));
		o++;
	}
	return (ft_malloc2(tab, str, compteur, c));
}

static void	ft_assign2(int *i, int *n, int *compteur)
{
	*i = 0;
	*n = 0;
	*compteur = 0;
}

char	**ft_split2(char const *s, char c)
{
	int		i;
	int		n;
	int		compteur;
	char	**tab;

	ft_assign2(&i, &n, &compteur);
	if (!s)
		return (NULL);
	while (s[i])
	{
		n = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			n++;
		}
		if (n > 0)
			compteur++;
	}
	tab = malloc(sizeof(char *) * (compteur + 1));
	if (!(tab))
		return (ft_free2(tab, 0));
	return (ft_malloc_string2(tab, s, compteur, c));
}
