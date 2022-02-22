/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:39:44 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/13 17:36:42 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	child_fork(t_data *data, t_cmd *cmd, char **path, int i)
{
	fd_pipe_child(data, cmd, i);
	exec_cmd(data, cmd, path);
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
			exit(ft_error(FORK));
		if (child == 0)
			child_fork(data, cmd, path, i);
		fd_pipe_parent(data, cmd, i);
		if (return_value(0, 1) == -117 || return_value(0, 1) == -118)
			break;
		i++;
		cmd = cmd->next;
		
	}
	parent_loop(data, tmp, 0, child);
	return (return_value(0, 1));
}

int	exec_data(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**path;

	i = 0;
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
			exit(ft_error(MALLOC));
	}
	printf("\n==MTN==\n");
	i = loop_exec(data, cmd, 0, path);
	if (path != NULL)
		free_tab(path);
	// printf("\n==DONE==\n");
	return (return_value(i, 0));
}
