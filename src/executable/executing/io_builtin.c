/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:23:21 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/15 12:23:28 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	one_pipe_close(t_data *data, t_cmd *cmd)
{
	static int	ret[2];

	(void)data;
	if (cmd->infile != -1)
		ret[0] = close(cmd->infile);
	if (cmd->outfile != -1)
		ret[1] = close(cmd->outfile);
	if ((ret[0] < 0) || (ret[1] < 0))
		exit(ft_error(CLOSE));
	return (0);
}

int	one_pipe_dup(t_data *data, t_cmd *cmd)
{
	static int	ret[2];

	(void)data;
	if (cmd->infile != -1)
		ret[0] = dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile != -1)
		ret[1] = dup2(cmd->outfile, STDOUT_FILENO);
	if ((ret[0] < 0) || (ret[1] < 0))
		exit(ft_error(DUP2));
	return (0);
}
