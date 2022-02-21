/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:22:56 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/21 11:52:15 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	first_pipe_p(t_data *data, t_cmd *cmd)
{
	static int	ret[3];

	if (data->nbr_pipe != 0)
		ret[0] = close(data->pipe_odd[1]);
	if (cmd->infile != -1)
		ret[1] = close(cmd->infile);
	if (cmd->outfile != -1)
		ret[2] = close(cmd->outfile);
	if ((ret[0] < 0) || (ret[1] < 0) || (ret[2] < 0))
		exit(ft_error(CLOSE));
}

void	random_pipe_p(t_data *data, t_cmd *cmd, int i)
{
	static int	ret[6];

	if (i % 2 == 0)
	{
		ret[0] = close(data->pipe_even[0]);
		ret[1] = close(data->pipe_odd[1]);
	}
	else
	{
		ret[2] = close(data->pipe_even[1]);
		ret[3] = close(data->pipe_odd[0]);
	}
	if (cmd->infile != -1)
		ret[4] = close(cmd->infile);
	if (cmd->outfile != -1)
		ret[5] = close(cmd->outfile);
	if ((ret[0] < 0) || (ret[1] < 0) || (ret[2] < 0)
		|| (ret[3] < 0) || (ret[4] < 0) || (ret[5] < 0))
		exit(ft_error(CLOSE));
}

void	last_pipe_p(t_data *data, t_cmd *cmd, int i)
{
	static int	ret[4];

	if (i % 2 == 0)
	{
		ret[0] = close(data->pipe_even[0]);
	}
	else
	{
		ret[1] = close(data->pipe_odd[0]);
	}
	if (cmd->infile != -1)
		ret[2] = close(cmd->infile);
	if (cmd->outfile != -1)
		ret[3] = close(cmd->outfile);
	if ((ret[0] < 0) || (ret[1] < 0) || (ret[2] < 0) || (ret[3] < 0))
		exit(ft_error(CLOSE));
}

int	parent_process(t_data *data, int i, int child)
{
	int	wstatus;

	waitpid(child, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		if (i == data->nbr_cmd - 1)
			return_value(WEXITSTATUS(wstatus), 0);
		if (WEXITSTATUS(wstatus) == 131 || WEXITSTATUS(wstatus) == 130)
			exit(return_value(0, 1));
	}
	else if (WIFSIGNALED(wstatus) == 1)
	{
		if (WTERMSIG(wstatus) == 2 || WTERMSIG(wstatus) == 3)
		{
			ft_putendl_fd("", STDOUT_FILENO);
			return_value(WTERMSIG(wstatus) + 128, 0);
			come_back_prompt(&data);
		}
	}
	else
		return (return_value(0, 1));
	return (return_value(0, 1));
}

void	parent_fork(t_data *data, t_cmd *cmd, int i, int child)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	fd_pipe_parent(data, cmd, i);
	parent_process(data, i, child);
}
