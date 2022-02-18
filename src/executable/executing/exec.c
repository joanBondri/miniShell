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

int	one_builtin(t_data *data, t_cmd *cmd)
{
	data->save_out = dup(STDOUT_FILENO);
	data->save_in = dup(STDIN_FILENO);
	one_pipe_dup(data, cmd);
	return_value(call_builtin(data, cmd, 0), 0);
	dup2(data->save_out, STDOUT_FILENO);
	dup2(data->save_in, STDIN_FILENO);
	close(data->save_in);
	close(data->save_out);
	one_pipe_close(data, cmd);
	return (return_value(0, 1));
}

int	pipe_fork(t_data *data, int i, int child)
{
	piper(data, i);
	child = fork();
	if (child == -1)
		exit(ft_error(FORK));
	return (child);
}

int	parent_process(t_data *data, int i, int child)
{
	int	wstatus;

	// fd_pipe_parent(data, cmd, i);
	// if (i < data->nbr_cmd - 1)
		// loop_exec(data, cmd->next, i, path);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	// printf("%d\n", child);
	waitpid(child, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		// value = WEXITSTATUS(wstatus);
		if (i == data->nbr_cmd - 1)
			return_value(WEXITSTATUS(wstatus), 0);
		if (WEXITSTATUS(wstatus) == 131 || WEXITSTATUS(wstatus) == 130)
			exit(return_value(0,1));
	}
	else if (WIFSIGNALED(wstatus) == 1)
	{
		if (WTERMSIG(wstatus) == 2 || WTERMSIG(wstatus) == 3)
		{
			// kill(-(child), SIGINT);
			ft_putendl_fd("", STDOUT_FILENO);
			return_value(WTERMSIG(wstatus) + 128, 0);
		}
	}
	else
		return (return_value(0, 1));
	return (return_value(0, 1));
}

void	exec_builtin(t_data *data, t_cmd *cmd)
{
	int	value;

	value = call_builtin(data, cmd, 0);
	free_data_cmd2(data);
	if (value > -1)
	{
		//if (i == data->nbr_cmd - 1)
		//	return_value(value, 0);
		//exit(return_value(0, 1));
		exit(return_value(value, 0));
	}
}		

void	exec_other_cmd(t_data *data, t_cmd *cmd, char **path)
{
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

int	loop_exec(t_data *data, t_cmd *cmd, int i, char **path)
{
	int	child;
	// int	wstatus;
	// int	value;
	i++;
	signal(SIGINT, handler_int_child);
	signal(SIGQUIT, handler_quit);
	if (data->nbr_cmd == 1 && is_builtin(cmd->arg[0]) == 1)
		return (one_builtin(data, cmd));
	piper(data, i);
	child = fork();
	if (child == -1)
		exit(ft_error(FORK));
	//child = pipe_fork(data, i, 0);
	if (child == 0)
	{
		fd_pipe_child(data, cmd, i);
		if (is_builtin(cmd->arg[0]) == 1)
			exec_builtin(data, cmd);
		// {
			// value = call_builtin(data, cmd, 0);
			// free_data_cmd2(data);
			// if (value > -1)
			// {
				// if (i == data->nbr_cmd - 1)
					// return_value(value, 0);
				// exit(return_value(0, 1));
				// exit(return_value(value, 0));
			// }
		// }
		else
			exec_other_cmd(data, cmd, path);
		// {
			// if (path == NULL)
			// {
				// print_free(ft_strjoin3("minishell: ", cmd->arg[0],
						// ": No such file or directory\n"), STDERR_FILENO);
				// exit(return_value(127, 0));
			// }
			// if (put_prepath(cmd, path) == 0)
			// {
				// print_free(ft_strjoin3("minishell: ", cmd->arg[0],
						// ": command not found\n"), STDERR_FILENO);
				// close_fd(cmd);
				// exit(return_value(127, 0));
			// }
			// else
				// exec_check(data, cmd);
			// if (execve(cmd->arg[0], cmd->arg, data->env) == -1)
				// exit(ft_error(EXECVE));
		// }
	}
	else
	{
		fd_pipe_parent(data, cmd, i);
		if (i < data->nbr_cmd - 1)
			loop_exec(data, cmd->next, i, path);
		parent_process(data, i, child);
		// signal(SIGINT, SIG_IGN);
		// signal(SIGQUIT, SIG_IGN);
		// waitpid(child, &wstatus, 0);
		// if (WIFEXITED(wstatus))
		// {
			// value = WEXITSTATUS(wstatus);
			// if (i == data->nbr_cmd - 1)
				// return_value(WEXITSTATUS(wstatus), 0);
		// }
		// else if (WIFSIGNALED(wstatus) == 1)
		// {
			// if (WTERMSIG(wstatus))
			// {
				// ft_putendl_fd("", STDOUT_FILENO);
				// return (return_value(WTERMSIG(wstatus) + 128, 0));
			// }
		// }
		// else
			// return (return_value(0, 1));
	}
	// if (i == data->nbr_cmd - 1)
	// 	return_value(value, 0);
	// printf("aslka12dlakdlakd\n");
	return (return_value(0, 1));
}

int	exec_data(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**path;
	// int		value;
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (data->env[i] == NULL)
	{
		path = NULL;
		//print_free(ft_strjoin3("minishell: ", cmd->arg[0],
		//		": No such file or directory\n"), STDERR_FILENO);
		//return (return_value(127, 0));
	}
	else
	{
		path = ft_split2(data->env[i] + 5, ':');
		if (!path)
			exit(ft_error(MALLOC));
	}
	i = -1;
	loop_exec(data, cmd, i, path);
	if (path != NULL)
		free_tab(path);
	return (return_value(0, 1));
}
