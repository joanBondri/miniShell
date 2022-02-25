/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:04:17 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/22 20:00:06 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	no_path(t_data *data, t_cmd *cmd)
{
	char	*tmp;

	if (execve(cmd->arg[0], cmd->arg, data->env) == -1)
	{
		tmp = ft_strjoin("minishell: ", cmd->arg[0]);
		perror(tmp);
		free(tmp);
		if (errno == 2)
			ft_exit_child(return_value(127, 0), data);
		if (errno == 13)
			ft_exit_child(return_value(126, 0), data);
	}
}

void	exec_builtin(t_data *data, t_cmd *cmd, int i)
{
	int	value;

	value = call_builtin(data, cmd, 0);
	fd_pipe_parent(data, cmd, i);
	ft_exit_child(return_value(value, 0), data);
}		

void	exec_other_cmd(t_data *data, t_cmd *cmd, char **path)
{
	if (ft_strfind(cmd->arg[0], '/') != -1)
	{
		exec_check(data, cmd);
		if (execve(cmd->arg[0], cmd->arg, data->env) == -1)
			ft_exit_child(ft_error(EXECVE), data);
	}
	if (path == NULL)
		no_path(data, cmd);
	if (put_prepath(data, cmd, path) == 0)
	{
		print_free(ft_strjoin3("minishell: ", cmd->arg[0],
				": command not found\n"), STDERR_FILENO);
		close_fd(cmd);
		ft_exit_child(return_value(127, 0), data);
	}
	else
		exec_check(data, cmd);
	if (execve(cmd->arg[0], cmd->arg, data->env) == -1)
		ft_exit_child(ft_error(EXECVE), data);
}

void	exec_cmd(t_data *data, t_cmd *cmd, char **path, int i)
{
	if (is_builtin(cmd->arg[0]) == 1)
		exec_builtin(data, cmd, i);
	else
		exec_other_cmd(data, cmd, path);
}
