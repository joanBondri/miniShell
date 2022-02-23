/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 05:16:45 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/22 19:03:47 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

char	etranglement(char *s, bool *q, bool *dq)
{
	int		i;
	char	c;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			c = s[i];
			if (c == '\'')
				*q = !*q;
			else
				*dq = !*dq;
			i++;
			while (s[i] && s[i] != c)
				++i;
			if (!s[i])
				break ;
			if (c == '\'')
				*q = !*q;
			else
				*dq = !*dq;
		}
	}
	return (c);
}

char	entanglement(char *s)
{
	char	c;
	bool	q;
	bool	dq;

	dq = false;
	q = false;
	c = etranglement(s, &q, &dq);
	if (q || dq)
		return (c);
	return (0);
}

void	check_quotes(char *s)
{
	char	c;

	c = entanglement(s);
	if (c)
		ft_unexpected_token(c, NULL);
}

char	*assemblage_concateneur(char *s1)
{
	static char	*str = NULL;
	char		*res;

	if (!s1)
	{
		res = str;
		str = NULL;
		return (res);
	}
	res = ft_strjoin_mod23(str, s1);
	str = res;
	add_lst_malloc(str);
	return (NULL);
}
