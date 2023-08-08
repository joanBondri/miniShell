/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 07:04:21 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/22 20:00:08 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

void	get_3_redirection(char *s, t_cmd *yop, t_token t)
{
	int		flag;
	int		fd;

	flag = O_CREAT | O_RDWR;
	if (!ft_strncmp(s, ">>", 2))
		flag = flag | O_APPEND;
	else
		flag = flag | O_TRUNC;
	fd = open(t.copy, flag,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd < 1)
		return (no_such_file(t.copy));
	if (yop->outfile > -1)
		close(yop->outfile);
	yop->outfile = fd;
	return ;
}

void	get_2_redirection(char *s, t_cmd *yop, t_token t)
{
	int		fd;

	if (!ft_strncmp(s, ">", 1))
		return (get_3_redirection(s, yop, t));
	fd = open(t.copy, O_RDONLY);
	if (fd < 1)
		return (no_such_file(t.copy));
	if (yop->change_in)
	{
		close(fd);
		return ;
	}
	if (yop->infile > -1)
		close(yop->infile);
	yop->infile = fd;
}

void	temp_function_get_redir(char *str, int i, t_data *dt, t_cmd *focus)
{
	t_token	t;

	t = (t_token){0};
	if (!ft_strncmp(">>", str + i, 2))
		assemblage_file_name_red(str + i + 2, &t, dt);
	else
		assemblage_file_name_red(str + i + 1, &t, dt);
	get_2_redirection(str + i, focus, t);
	if (change_mind("no", true))
		return ;
	if (!ft_strncmp(">>", str + i, 2) || !ft_strncmp("<<", str + i, 2))
		focus->path = ft_strlreplace(str, "", i, t.length + 2);
	else
		focus->path = ft_strlreplace(str, "", i, t.length + 1);
	add_lst_malloc((void *)focus->path);
}

void	get_redirection(t_cmd *focus, t_data *dt)
{
	int			i;
	bool		q;
	bool		p;

	i = 0;
	q = false;
	p = false;
	while (focus->path[i])
	{
		if (focus->path[i] == '\'' && !p)
			q = !q;
		if (focus->path[i] == '"' && !q)
			p = !p;
		if (ft_strchr("<>", focus->path[i]) && !q && !p)
			temp_function_get_redir(focus->path, i, dt, focus);
		else
			i++;
		if (change_mind("no", false))
			return ;
	}
}

void	near_token(char *s, t_data *dt)
{
	int		i;
	t_token	t;

	i = 0;
	while (s[i] && ft_strchr(" \t\f\v", s[i]))
		i++;
	next_token(s + i, &t, dt);
	if (!(t.copy))
		return (ft_unexpected_token('\0', "newline"));
	else
		return (ft_unexpected_token('\0', t.copy));
}
