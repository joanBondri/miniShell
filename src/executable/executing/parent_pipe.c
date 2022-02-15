/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:22:56 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/15 12:23:04 by xchalle          ###   ########.fr       */
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
