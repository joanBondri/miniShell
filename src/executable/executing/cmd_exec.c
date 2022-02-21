/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:04:17 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/21 17:05:12 by xchalle          ###   ########.fr       */
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
