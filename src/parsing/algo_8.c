/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 07:04:33 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/22 18:51:48 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

char	*ft_strjoin_mod23(char const *str1, char const *str2)
{
	long	i;
	char	*s1;
	char	*s2;
	char	*res;

	s1 = (char *)str1;
	s2 = (char *)str2;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!(res))
		return (NULL);
	i = -1;
	while ((size_t)++i < ft_strlen(s1))
		res[i] = s1[i];
	i = -1;
	while ((size_t)++i < ft_strlen(s2))
		res[i + ft_strlen(s1)] = s2[i];
	res[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (res);
}

void	parser_director_2(char *s, t_data **dt)
{
	t_cmd			*buff;

	buff = (*dt)->cmd;
	check_redirection(s, *dt);
	if (change_mind("no", false))
		return ;
	while (buff)
	{
		get_redirection(buff, *dt);
		if (change_mind("no", false))
			return ;
		expand_rest_envvar(buff, *dt);
		interprate_sequence(buff, *dt);
		if (change_mind("no", false))
			return ;
		buff = buff->next;
	}
}

int	parser_director(char *s, t_data **dt)
{
	signal(SIGINT, handler_int_parser);
	signal(SIGQUIT, handler_quit_parser);
	check_quotes(s);
	if (change_mind("yes", false))
		return (0);
	divide_pip(s, dt);
	do_all_heredoc(*dt);
	if (change_mind("yes", false))
		return (0);
	check_pips(s);
	if (change_mind("yes", false))
		return (0);
	check_par(s);
	if (change_mind("yes", false))
		return (0);
	if (return_value(0, 1) == -117 || return_value(0, 1) == -116)
		return (return_value(return_value(0, 1) + 247, 0));
	parser_director_2(s, dt);
	if (change_mind("yes", false))
		return (0);
	get_data(*dt);
	if (return_value(0, 1) == -117 || return_value(0, 1) == -116)
		return (return_value(return_value(0, 1) + 247, 0));
	exec_data(*dt, (*dt)->cmd);
	return (0);
}

bool	ft_trim(char *s, char c)
{
	if (s[0] != c || s[ft_strlen(s) - 1] != c)
		return (false);
	ft_strlcpy(s, s + 1, ft_strlen(s + 1) + 1);
	s[ft_strlen(s) - 1] = (char)0;
	return (true);
}	

void	interprate_sequence(t_cmd *buff, t_data *dt)
{
	int		i;
	t_token	t;

	i = 0;
	add_lst_arg(NULL, false);
	while (buff->path[i])
	{
		while (buff->path[i] && ft_strchr(" \t\v\f", buff->path[i]))
			i++;
		if (!buff->path[i])
			break ;
		t = (t_token){0};
		assemblage_file_name_red(buff->path + i, &t, dt);
		if (change_mind("no", false))
			return ;
		if (t.status != MSWHITESPACE)
			add_lst_arg(t.copy, false);
		i += t.length;
	}
	buff->arg = add_lst_arg(NULL, true);
}
