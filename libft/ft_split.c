/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:08:05 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 10:51:23 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**ft_malloc(char **tab, const char *str, int compteur, char c)
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

static char	**ft_malloc_string(
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
			return (ft_free(tab));
		o++;
	}
	return (ft_malloc(tab, str, compteur, c));
}

static void	ft_assign(int *i, int *n, int *compteur)
{
	*i = 0;
	*n = 0;
	*compteur = 0;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		n;
	int		compteur;
	char	**tab;

	ft_assign(&i, &n, &compteur);
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
		return (NULL);
	return (ft_malloc_string(tab, s, compteur, c));
}
