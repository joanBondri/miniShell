/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 04:27:18 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/25 20:08:20 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

int	error_pip(void)
{
	ft_putstr_fd("minishell : error pip\n", 2);
	return_value(1, 0);
	change_mind("yes", true);
	return (0);
}

int	go_heredoc(char *str, t_cmd *buff, t_data *dt)
{
	static int	pip[2];
	char		*del;
	t_token		tt;
	int			child;

	tt = (t_token){0};
	del = next_del(str, &tt, dt);
	add_lst_malloc(del);
	if (!del)
		return (0);
	signal(SIGQUIT, SIG_IGN);
	if (manage_pid(pip, buff) != 80)
		return (0);
	child = fork();
	if (child == -1)
		exit(ft_error(FORK));
	if (child == 0)
		determine_content_herdoc(del, pip, dt);
	if (!manage_parent(pip))
		return (0);
	close(pip[1]);
	signal(SIGINT, handler_int);
	return (tt.length);
}

void	check_if_here_last(char *str, t_cmd *buff)
{
	int		i;

	i = 0;
	buff->change_in = false;
	while (str[i])
	{
		if (!ft_strncmp("<<", str + i, 2))
		{
			i++;
			buff->change_in = true;
		}
		else if (!ft_strncmp("<", str + i, 1))
			buff->change_in = false;
		i++;
	}
}

void	catch_heredoc(char *str, t_cmd *buff, t_data *dt)
{
	int		i;
	bool	q;
	bool	dq;
	int		res;

	q = false;
	dq = false;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && !dq)
			q = !q;
		else if (str[i] == '"' && !q)
			dq = !dq;
		else if (!dq && !q && !ft_strncmp("<<", str + i, 2))
		{
			res = go_heredoc(str + i, buff, dt);
			if (res == 0)
				return ;
			buff->path = ft_strlreplace(str, "", i, res);
			add_lst_malloc((void *)buff->path);
			str = buff->path;
			i--;
		}
	}
}

void	do_all_heredoc(t_data *dt)
{
	t_cmd	*buff;

	buff = dt->cmd;
	while (buff)
	{
		check_if_here_last(buff->path, buff);
		catch_heredoc(buff->path, buff, dt);
		if (change_mind("no", false))
			return ;
		buff = buff->next;
	}
}
