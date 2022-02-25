/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 07:03:33 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/25 20:14:17 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

void	check_par(char *s)
{
	int		i;
	int		j;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '$' && s[i + 1] == '{')
		{
			j = i;
			i += 1;
			while (s[++i])
			{
				if (s[i] == '}')
					break ;
				if (i == j + 2 && ft_isdigit(s[i]))
					return (ft_bad_substitution(s + j));
				if (!ft_isalnum(s[i]) && s[i] != '_')
					return (ft_bad_substitution(s + j));
			}
			if (s[i] != '}' || (s[i + 1] && !ft_strchr(" \t\v\f", s[i + 1])))
				return (ft_bad_substitution(s + j));
		}
	}
	return ;
}

void	next_token(char *s, t_token *t, t_data *dt)
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
	add_lst_malloc(t->copy);
}

int	check_redirection_file(char *str, t_data *dt)
{
	int		len;
	t_token	t;

	if (ft_strlen(str) < 2)
	{
		ft_unexpected_token((char)0, "newline");
		return (0);
	}
	if (ft_strchr("<>", str[1]))
	{
		len = 2;
		if (str[1] != str[0])
		{
			ft_unexpected_token(str[1], NULL);
			return (2);
		}
	}
	else
		len = 1;
	assemblage_file_name_red(str + len, &t, dt);
	t.copy = NULL;
	return (len);
}

void	check_redirection(char *str, t_data *dt)
{
	int			i;
	bool		q;
	bool		p;

	i = -1;
	q = false;
	p = false;
	while (str[++i])
	{
		if (str[i] == '\'' && !p)
			q = !q;
		if (str[i] == '"' && !q)
			p = !p;
		if (ft_strchr("<>", str[i]) && !q && !p)
			i += check_redirection_file(str + i, dt);
		if (change_mind("no", false))
			return ;
	}
}

char	*ft_exit_malloc(void)
{
	ft_putstr_fd("error_malloc\n", 2);
	free_all_lst_malloc();
	exit(1);
	return (NULL);
}
