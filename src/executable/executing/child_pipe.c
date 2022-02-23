/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:23:40 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/21 15:52:00 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	pipe_even_c(t_data *data, t_cmd *cmd)
{
	static int	ret[8];

	ret[4] = close(data->pipe_odd[0]);
	if (cmd->infile != -1)
		ret[0] = dup2(cmd->infile, STDIN_FILENO);
	else
		ret[1] = dup2(data->pipe_even[0], STDIN_FILENO);
	if (cmd->outfile != -1)
		ret[2] = dup2(cmd->outfile, STDOUT_FILENO);
	else
		ret[3] = dup2(data->pipe_odd[1], STDOUT_FILENO);
	if ((ret[0] < 0) || (ret[1] < 0) || (ret[2] < 0) || (ret[3] < 0))
		ft_exit_child(ft_error(DUP2), data);
	if (ret[4] < 0)
		ft_exit_child(ft_error(CLOSE), data);
	return (0);
}

int	pipe_odd_c(t_data *data, t_cmd *cmd)
{
	static int	ret[8];

	ret[4] = close(data->pipe_even[0]);
	if (cmd->infile != -1)
		ret[0] = dup2(cmd->infile, STDIN_FILENO);
	else
		ret[1] = dup2(data->pipe_odd[0], STDIN_FILENO);
	if (cmd->outfile != -1)
		ret[2] = dup2(cmd->outfile, STDOUT_FILENO);
	else
		ret[3] = dup2(data->pipe_even[1], STDOUT_FILENO);
	if ((ret[0] < 0) || (ret[1] < 0) || (ret[2] < 0) || (ret[3] < 0))
		ft_exit_child(ft_error(DUP2), data);
	if (ret[4] < 0)
		ft_exit_child(ft_error(CLOSE), data);
	return (0);
}

int	random_pipe_c(t_data *data, t_cmd *cmd, int i)
{
	if ((i % 2) == 0)
		pipe_even_c(data, cmd);
	if ((i % 2) == 1)
		pipe_odd_c(data, cmd);
	return (0);
}

int	last_pipe_c(t_data *data, t_cmd *cmd, int i)
{
	static int	ret[8];

	if (i % 2 == 0)
		ret[1] = dup2(data->pipe_even[0], STDIN_FILENO);
	if (i % 2 == 1)
		ret[2] = dup2(data->pipe_odd[0], STDIN_FILENO);
	if (cmd->infile != -1)
		ret[0] = dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile != -1)
		ret[3] = dup2(cmd->outfile, STDOUT_FILENO);
	if ((ret[0] < 0) || (ret[1] < 0) || (ret[2] < 0) || (ret[3] < 0))
		ft_exit_child(ft_error(DUP2), data);
	return (0);
}

int	first_pipe_c(t_data *data, t_cmd *cmd)
{
	static int	ret[4];

	if (data->nbr_pipe != 0)
		ret[3] = close(data->pipe_odd[0]);
	if (cmd->infile != -1)
		ret[0] = dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile != -1)
		ret[1] = dup2(cmd->outfile, STDOUT_FILENO);
	else if (data->nbr_pipe > 0)
		ret[2] = dup2(data->pipe_odd[1], STDOUT_FILENO);
	if ((ret[0] < 0) || (ret[1] < 0) || (ret[2] < 0))
		ft_exit_child(ft_error(DUP2), data);
	if (ret[3] < 0)
		ft_exit_child(ft_error(CLOSE), data);
	return (0);
}
