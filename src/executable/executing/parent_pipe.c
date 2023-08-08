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

#include "pip.h"

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
		ft_exit_child(ft_error(CLOSE), data);
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
		ft_exit_child(ft_error(CLOSE), data);
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
		ft_exit_child(ft_error(CLOSE), data);
}

int	parent_process(t_data *data, int i, int child)
{
	int	wstatus;
	int	return_status;

	return_status = 0;
	(void)child;
	wait(&wstatus);
	if (WIFEXITED(wstatus))
	{
		if (i == data->nbr_cmd - 1)
			return_status = WEXITSTATUS(wstatus);
		if (WEXITSTATUS(wstatus) == -116 || WEXITSTATUS(wstatus) == -117)
			ft_exit_child(return_value(WEXITSTATUS(wstatus) + 247, 0), data);
	}
	else if (WIFSIGNALED(wstatus) == 1)
	{
		if (WTERMSIG(wstatus) == 2 || WTERMSIG(wstatus) == 3)
		{
			rl_on_new_line();
			rl_replace_line ("", 0);
			return_status = return_value(WTERMSIG(wstatus) + 128, 0);
		}
	}
	else
		return (return_value(0, 1));
	return (return_value(return_status, 0));
}

void	parent_fork(t_data *data, t_cmd *cmd, int i, int child)
{
	(void)cmd;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	parent_process(data, i, child);
}
