/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 07:04:14 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/22 14:31:12 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

void	ambigus_redirect(char *s)
{	
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (s[i] && ft_strchr(" \t\f\v", s[i]))
		i++;
	while (s[i + j] && !ft_strchr(" \t\f\v", s[i + j]))
		j++;
	res = ft_strndup(s + i, j);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(res, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	free(res);
	free_all_lst_malloc();
	change_mind("yes", true);
	return_value(1, 0);
}

bool	assem_2(char *s, t_data *dt, int *i)
{
	bool	p;
	t_token	t;

	p = false;
	while (s[*i])
	{
		t = (t_token){0};
		next_token(s + *i, &t, dt);
		if ((t.status >= MSPIP && t.status <= MSRED_OUT)
			|| t.status == MSWHITESPACE)
			break ;
		*i += t.length;
		if (t.status == MSVARENV && t.sub_status == MSNONE
			&& !ft_strncmp(t.copy, "", 23))
			p = true;
		else
			p = false;
		if (t.copy)
			assemblage_concateneur(t.copy);
	}
	return (p);
}

void	assemblage_file_name_red(char *s, t_token *tt, t_data *dt)
{
	int		i;
	bool	p;

	i = 0;
	while (s[i] && ft_strchr(" \t\f\v", s[i]))
		i++;
	p = assem_2(s, dt, &i);
	tt->copy = assemblage_concateneur(NULL);
	tt->length = i;
	if (p)
		ambigus_redirect(s);
	else if (!(tt->copy))
		near_token(s, dt);
}

char	*ft_strndup(char *s, int size)
{
	int		i;
	char	*res;

	i = 0;
	if (size < 0 || !s)
		return (NULL);
	i = ft_strlen(s);
	if (size < i)
		i = size;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, i + 1);
	return (res);
}

void	check_pips(char *s)
{
	if (check_pip_double(s))
		ft_unexpected_token('|', NULL);
}
