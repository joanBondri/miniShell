/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 07:03:49 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/17 23:11:30 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

char	*interrog(void)
{
	char	*res;

	res = ft_itoa(return_value(0, 1));
	if (!res)
		ft_error(MALLOC);
	return (res);
}

void	set_null_token_varenv(t_token *t)
{
	t->sub_status = MSNONE;
	t->copy = ft_strdup("");
	return ;
}

void	insultant(char *res, t_token *t)
{
	int	i;

	i = 0;
	while (res[i] && ft_strchr(" \t\f\v\n", res[i]))
		i++;
	if (ft_strlen(res) == 0)
		t->sub_status = MSVOID;
	else if ((size_t)i == ft_strlen(res))
		t->sub_status = MSWHITESPACE;
	t->sub_status = MSWORD;
}

void	develope_varenv(t_token *t, char *s, t_data *dt)
{
	char	*res;

	if (!ft_strncmp("$?", s, 2) || !ft_strncmp("${?}", s, 4))
	{
		*t = (t_token){.copy = interrog(),
			.status = MSVARENV, .sub_status = MSWORD};
		t->length = 4;
		if (!ft_strncmp("$?", s, 2))
			t->length = 2;
		return ;
	}
	t->length = find_variable_in_str(s, &(t->copy));
	if (-1 == t->length)
		return (set_null_token_varenv(t));
	res = find_env(t->copy, dt);
	free(t->copy);
	if (!res)
		return (set_null_token_varenv(t));
	t->copy = res;
	insultant(res, t);
}

void	develope_redirection(t_token *t, char *s)
{
	t->start = s;
	if (t->status == MSRED_HER || t->status == MSRED_APP)
		t->copy = ft_strndup(s, 2);
	else
		t->copy = ft_strndup(s, 1);
	t->length = ft_strlen(t->copy);
}
