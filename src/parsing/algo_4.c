/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 07:04:03 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/17 07:11:21 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

char	*ft_strlreplace(char *s1, char *s2, int index, int len)
{
	char	*start;
	char	*end;
	char	*buff;
	char	*res;

	if (!s1 || len < 0 || index < 0)
		return (NULL);
	if ((size_t)index + len > ft_strlen(s1))
		end = NULL;
	else
		end = ft_strdup(s1 + index + len);
	start = ft_strndup(s1, index);
	buff = ft_strjoin_mod23(start, s2);
	res = ft_strjoin_mod23(buff, end);
	if (end)
		free(end);
	if (start)
		free(start);
	if (buff)
		free(buff);
	return (res);
}

void	yop(char *s, int i, t_data *dt, t_token *t)
{
	t_token	tok;
	char	*res;

	while (s[--i] != '\"')
	{
		if (s[i] != '$')
			continue ;
		next_token(s + i, &tok, dt);
		if (tok.length == -1)
			continue ;
		if (tok.status == MSVARENV)
		{
			res = ft_strlreplace(t->copy, tok.copy, i - 1, tok.length);
			if (!res)
				return ((void)ft_error(MALLOC));
			if (t->copy)
				free(t->copy);
			t->copy = res;
		}
	}
}

void	develope_dquote(t_token *t, char *s, t_data *dt)
{
	int		i;

	i = 1;
	while (s[i] && s[i] != '"')
		i++;
	t->start = s;
	t->length = i + 1;
	if (i == 1)
		t->sub_status = MSVOID;
	else
		t->sub_status = MSWORD;
	t->copy = ft_strndup(s + 1, i - 1);
	yop(s, i, dt, t);
}

void	develope_word(t_token *t, char *s)
{
	int		i;

	t->status = MSWORD;
	if (!s[0])
	{
		t->length = 0;
		t->sub_status = MSVOID;
		return ;
	}
	i = 1;
	while (s[i] && !ft_strchr("<>|$'\" ", s[i]))
		i++;
	t->copy = ft_strndup(s, i);
	t->length = ft_strlen(t->copy);
	return ;
}

void	develope_quote(t_token *t, char *s)
{
	int		i;

	i = 1;
	while (s[i] != '\'')
		i++;
	t->start = s;
	t->length = i + 1;
	if (i == 1)
		t->sub_status = MSVOID;
	else
		t->sub_status = MSWORD;
	t->copy = ft_strndup(s + 1, i - 1);
	return ;
}
