/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 00:17:19 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/17 04:28:00 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

void	ft_exit_malloc(void)
{
	printf("error_malloc");
	free_all_lst_malloc();
	exit(1);
}

char	*switch_varenv(char *str, t_data *dt)
{
	int		i;
	t_token	t;
	char	*res;

	i = -1;
	while (str[++i])
	{
		t = (t_token){0};
		if (str[i] == '$')
		{
			next_token(str + i, &t, dt);
			if (t.status != MSVARENV && i++)
				continue ;
			res = ft_strlreplace(str, t.copy, i, t.length);
			add_lst_malloc((void *)res);
			if (!res)
			{
				ft_exit_malloc();
				return (NULL);
			}
			str = res;
			i += (int)ft_strlen(t.copy) - 1;
		}
	}
	return (str);
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
			next_token(s + *i, &t, dt);
		printf("t_copy = %s, %i, %s\n", t.copy, *i, s + *i);
		if ((t.status >= MSPIP && t.status <= MSRED_OUT)
			|| t.status == MSWHITESPACE)
			return ;
		*i += t.length;
		if (t.copy)
			assemblage_concateneur(t.copy);
	}
}

char	*next_del(char *s, t_token *tt, t_data *dt)
{
	int		i;

	i = 2;
	while (s[i] && ft_strchr(" \t\f\v", s[i]))
		i++;
	next_del2(s, &i, dt);
	tt->copy = assemblage_concateneur(NULL);
	tt->length = i;
	if (!(tt->copy))
	{
		near_token(s, dt);
		return (0);
	}
	return (tt->copy);
}
