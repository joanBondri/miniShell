/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 07:03:42 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/22 14:27:20 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

void	find_type_token(char *tb, char *s, t_token *t, t_data *dt)
{
	if (ft_strncmp(tb, s, ft_strlen(tb)) && ft_strchr("<>|$\'\"", s[0]))
		return ;
	t->start = s;
	if (!ft_strchr("<>|$\'\"", s[0]))
		t->status = MSWORD;
	else if (s[0] == '$'
		&& (!s[1] || (!ft_isalnum(s[1]) && !ft_strchr("_{?", s[1]))))
		t->status = MSWORD;
	if (t->status == MSVARENV)
		return (develope_varenv(t, s, dt));
	else if (t->status == MSQUOTE)
		return (develope_quote(t, s));
	else if (t->status == MSDQUOTE)
		return (develope_dquote(t, s, dt));
	else if (t->status == MSWORD)
		return (develope_word(t, s));
	else
		return (develope_redirection(t, s));
}

void	change_interrog(int res)
{
	t_data	*dt;

	dt = get_data(NULL);
	dt->return_value = res;
}

void	ft_unexpected_token(char c, char *s)
{
	(void)s;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (s)
		ft_putstr_fd(s, 2);
	else
		ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	free_all_lst_malloc();
	return_value(2, 0);
	change_mind("yes", true);
}

void	print_bad_sub(char *res)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(res, 2);
	ft_putstr_fd(": bad substitution\n", 2);
	free(res);
	free_all_lst_malloc();
	return_value(1, 0);
	change_mind("yes", true);
}

void	ft_bad_substitution(char *s)
{
	int		i;
	int		j;
	char	*res;

	i = 1;
	j = ft_strlen(s);
	while (s[++i])
	{
		if (s[i] == '}')
		{
			while (s[++i])
			{
				if (s[i] == ' ')
				{
					j = i;
					i = ft_strlen(s);
				}
			}
		}
	}
	res = ft_strndup(s, j);
	print_bad_sub(res);
}
