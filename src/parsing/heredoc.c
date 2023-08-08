/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 00:17:19 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/25 20:27:37 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

char	*switch_varenv(char **str, t_data *dt)
{
	int		i;
	t_token	t;
	char	*res;

	i = -1;
	while ((*str)[++i])
	{
		t = (t_token){0};
		if ((*str)[i] == '$')
		{
			next_token_2((*str) + i, &t, dt);
			if (t.status != MSVARENV && i++)
				continue ;
			res = ft_strlreplace((*str), t.copy, i, t.length);
			free(*str);
			if (!res)
				return ((char *)ft_exit_malloc());
			(*str) = res;
			i += (int)ft_strlen(t.copy) - 1;
			free(t.copy);
		}
	}
	return ((*str));
}

char	*assemblage_concateneur_2(char *s1)
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
	if (str)
		free(str);
	str = res;
	return (NULL);
}

void	next_token_2(char *s, t_token *t, t_data *dt)
{
	int			i;
	static char	*tb[] = {"|", "<<", ">>", "<", ">", "'", "\"", "$"};

	i = 0;
	while (s[i] && ft_strchr(" \t\v\f\n", s[i]))
		i++;
	if (i != 0)
	{
		t->status = MSWHITESPACE;
		t->length = i;
		return ;
	}
	t->start = s;
	i = -1;
	while (++i < 8)
	{
		*t = (t_token){0};
		t->status = i;
		find_type_token((char *)tb[i], s, t, dt);
		if (t->start)
			break ;
	}
}

void	next_del2(char *s, int *i, t_data *dt)
{
	t_token	t;

	while (s[*i])
	{
		t = (t_token){0};
		if (s[*i] == '$')
			develope_word(&t, s);
		else
			next_token_2(s + *i, &t, dt);
		if ((t.status >= MSPIP && t.status <= MSRED_OUT)
			|| t.status == MSWHITESPACE)
			return ;
		*i += t.length;
		if (t.copy)
		{
			assemblage_concateneur_2(t.copy);
			free(t.copy);
		}
	}
}

char	*next_del(char *s, t_token *tt, t_data *dt)
{
	int		i;

	i = 2;
	while (s[i] && ft_strchr(" \t\f\v", s[i]))
		i++;
	next_del2(s, &i, dt);
	tt->copy = assemblage_concateneur_2(NULL);
	tt->length = i;
	if (!(tt->copy))
	{
		near_token(s + 2, dt);
		return (0);
	}
	return (tt->copy);
}
