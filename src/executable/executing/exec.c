/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:39:44 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/21 15:53:37 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	exec_builtin(t_data *data, t_cmd *cmd)
{
	int	value;

	value = call_builtin(data, cmd, 0);
	free_data_cmd2(data);
	if (value > -1)
		exit(return_value(value, 0));
}		

void	exec_other_cmd(t_data *data, t_cmd *cmd, char **path)
{
	if (ft_strfind(cmd->arg[0], '/') != -1)
	{
		exec_check(data, cmd);
		if (execve(cmd->arg[0], cmd->arg, data->env) == -1)
			exit(ft_error(EXECVE));
	}
	if (path == NULL)
	{
		print_free(ft_strjoin3("minishell: ", cmd->arg[0],
				": No such file or directory\n"), STDERR_FILENO);
		exit(return_value(127, 0));
	}
	if (put_prepath(cmd, path) == 0)
	{
		print_free(ft_strjoin3("minishell: ", cmd->arg[0],
				": command not found\n"), STDERR_FILENO);
		close_fd(cmd);
		exit(return_value(127, 0));
	}
	else
		exec_check(data, cmd);
	if (execve(cmd->arg[0], cmd->arg, data->env) == -1)
		exit(ft_error(EXECVE));
}

void	exec_cmd(t_data *data, t_cmd *cmd, char **path)
{
	if (is_builtin(cmd->arg[0]) == 1)
		exec_builtin(data, cmd);
	else
		exec_other_cmd(data, cmd, path);
}

void	child_fork(t_data *data, t_cmd *cmd, char **path, int i)
{
	signal(SIGINT, handler_int_child);
	signal(SIGQUIT, handler_quit_child);
	fd_pipe_child(data, cmd, i);
	exec_cmd(data, cmd, path);
}

int	loop_exec(t_data *data, t_cmd *cmd, int i, char **path)
{
	int		child;
	t_cmd	*tmp;

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
		i++;
		cmd = cmd->next;
	}
	i = 0;
	cmd = tmp;
	while (i < data->nbr_cmd)
	{
		parent_fork(data, cmd, i, child);
		i++;
		cmd = cmd->next;
	}
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
	loop_exec(data, cmd, 0, path);
	if (path != NULL)
		free_tab(path);
	return (return_value(0, 1));
}
