/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:39:44 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/22 18:34:32 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	child_fork(t_data *data, t_cmd *cmd, char **path, int i)
{
	fd_pipe_child(data, cmd, i);
	exec_cmd(data, cmd, path, i);
}

void	parent_loop(t_data *data, t_cmd *cmd, int i, int child)
{
	while (i < data->nbr_cmd)
	{
		parent_fork(data, cmd, i, child);
		i++;
		cmd = cmd->next;
	}
}

int	loop_exec(t_data *data, t_cmd *cmd, int i, char **path)
{
	int		child;
	t_cmd	*tmp;

	signal(SIGINT, handler_int_parser);
	signal(SIGQUIT, handler_quit_parser);
	tmp = cmd;
	if (data->nbr_cmd == 1 && is_builtin(cmd->arg[0]) == 1)
		return (one_builtin(data, cmd));
	while (i < data->nbr_cmd)
	{
		piper(data, i);
		child = fork();
		if (child == -1)
			ft_exit_exec(ft_error(FORK), cmd);
		if (child == 0)
			child_fork(data, cmd, path, i);
		fd_pipe_parent(data, cmd, i);
		if (return_value(0, 1) == -117 || return_value(0, 1) == -116)
			break ;
		i++;
		cmd = cmd->next;
	}
	parent_loop(data, tmp, 0, child);
	return (return_value(0, 1));
}

int	exec_data_suit(t_data *data, t_cmd *cmd, char **path)
{
	int	i;

	i = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = loop_exec(data, cmd, 0, path);
	free_all_cmd(cmd);
	if (path != NULL)
		free_tab(path);
	return (return_value(i, 0));
}

int	exec_data(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**path;

	i = 0;
	check_t_free(data, NULL);
	free_lst_conditionnal();
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (data->env[i] == NULL)
		path = NULL;
	else
	{
		path = ft_split2(data->env[i] + 5, ':');
		if (!path)
			ft_exit_exec(ft_error(MALLOC), cmd);
	}
	data->path = path;
	return (exec_data_suit(data, cmd, path));
}
