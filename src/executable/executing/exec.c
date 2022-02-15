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

void	fd_pipe_child(t_data *data, t_cmd *cmd, int i)
{
	if (i == 0)
		first_pipe_c(data, cmd);
	else if (i == data->nbr_cmd - 1)
		last_pipe_c(data, cmd, i);
	else
		random_pipe_c(data, cmd, i);
}

void	fd_pipe_parent(t_data *data, t_cmd *cmd, int i)
{
	if (i == 0)
	{
		first_pipe_p(data, cmd);
	}
	else if (i == data->nbr_cmd - 1)
	{
		last_pipe_p(data, cmd, i);
	}
	else
		random_pipe_p(data, cmd, i);
}

void	piper(t_data *data, int i)
{
	if (i == data->nbr_cmd - 1)
	{
		return ;
	}
	else if ((i % 2 == 0))
	{
		if (pipe(data->pipe_odd) < 0)
			exit(ft_error(PIPE));
	}
	else
	{
		if (pipe(data->pipe_even) < 0)
			exit(ft_error(PIPE));
	}
}

int	loop_exec(t_data *data, t_cmd *cmd, int i, char **path)
{
	int	child;
	int	wstatus;
	int	value;

	i++;
	if (data->nbr_cmd == 1 && is_builtin(cmd->arg[0]) == 1)
	{
		signal(SIGINT, handler_int);
		signal(SIGQUIT, handler_int);
		data->save_out = dup(STDOUT_FILENO);
		data->save_in = dup(STDIN_FILENO);
		one_pipe_dup(data, cmd);
		return_value(call_builtin(data, cmd, 0), 0);
		dup2(data->save_out, STDOUT_FILENO);
		dup2(data->save_in, STDIN_FILENO);
		one_pipe_close(data, cmd);
		return (return_value(0, 1));
	}
	piper(data, i);
	child = fork();
	if (child == -1)
		exit(ft_error(FORK));
	else if (child == 0)
	{
		signal(SIGINT, handler_int);
		signal(SIGQUIT, handler_int);
		fd_pipe_child(data, cmd, i);
		if (is_builtin(cmd->arg[0]) == 1)
		{
			value = call_builtin(data, cmd, 0);
			if (value > -1)
			{
				//if (i == data->nbr_cmd - 1)
				//	return_value(value, 0);
				//exit(return_value(0, 1));
				exit(return_value(value, 0));
			}
		}
		else
		{
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
	}
	else
	{
		fd_pipe_parent(data, cmd, i);
		if (i < data->nbr_cmd - 1)
		{
			loop_exec(data, cmd->next, i, path);
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(child, &wstatus, 0);
		if (WIFEXITED(wstatus))
		{
			if (WIFSIGNALED(wstatus) == 1)
				ft_putendl_fd("\n", STDOUT_FILENO);
			value = WEXITSTATUS(wstatus);
		}
	}
	if (i == data->nbr_cmd - 1)
		return_value(value, 0);
	return (return_value(0, 1));
}

int	exec_data(t_data *data, t_cmd *cmd)
{
	int		i;
	int		value;
	char	**path;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	path = ft_split2(data->env[i] + 5, ':');
	if (!path)
		exit(ft_error(MALLOC));
	i = -1;
	value = loop_exec(data, cmd, i, path);
	free_tab(path);
	return (return_value(0, 1));
}
