/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:02:29 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/17 17:49:24 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	exec_check(t_data *data, t_cmd *cmd)
{
	struct stat	stat1;
	struct stat	stat2;

	(void)data;
	if (stat(cmd->arg[0], &stat1) != 0)
	{
		print_free(ft_strjoin3("minishell: ",
				cmd->arg[0], ": No such file or directory\n"), STDERR_FILENO);
		close_fd(cmd);
		ft_exit_child(127, data);
	}
	if (stat(cmd->arg[0], &stat2) == 0 && S_ISDIR(stat2.st_mode) == 1)
	{
		print_free(ft_strjoin3("minishell: ",
				cmd->arg[0], ": is a directory\n"), STDERR_FILENO);
		close_fd(cmd);
		ft_exit_child(126, data);
	}
	if (access(cmd->arg[0], X_OK) == -1)
	{
		print_free(ft_strjoin3("minishell: ",
				cmd->arg[0], ": Permission denied\n"), STDERR_FILENO);
		close_fd(cmd);
		ft_exit_child(126, data);
	}
}

int	abs_path(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->arg[0], "./", 2))
		return (1);
	if (!ft_strncmp(cmd->arg[0], "..", 2))
		return (1);
	if (!ft_strncmp(cmd->arg[0], "/", 1))
		return (1);
	if (!ft_strcmp(cmd->arg[0], "."))
		return (1);
	return (0);
}

int	loop_path(char **path, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin3(path[i], "/", *cmd);
		if (!tmp)
			ft_error(MALLOC);
		if (access(tmp, F_OK) == 0)
		{
			free(*cmd);
			*cmd = tmp;
			return (1);
		}
		free(tmp);
		i++;
	}
	return (0);
}

int	put_prepath(t_data *data, t_cmd *cmd, char **path)
{
	if (cmd->arg[0] == NULL)
		ft_exit_child(0, data);
	if (ft_strcmp(cmd->arg[0], "") == 0)
		return (0);
	if (abs_path(cmd) == 1)
		return (1);
	if (loop_path(path, &cmd->arg[0]) == 0)
		return (0);
	return (1);
}
