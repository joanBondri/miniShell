/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:32:49 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/10 13:35:56 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data	*get_data(t_data *dt)
{
	static t_data	*res;

	if (dt)
		res = dt;
	return (res);
}

int	close_fd(t_cmd *cmd)
{
	if (cmd->outfile > 0)
		close(cmd->outfile);
	if (cmd->infile > 0)
		close(cmd->infile);
	return (0);
}

void	free_data_cmd(void)
{
	t_cmd	*tmp;
	t_cmd	*cmd;
	t_data	*data;

	data = get_data(NULL);
	cmd = data->cmd;
	while (cmd != NULL)
	{
		tmp = cmd;
		cmd = cmd->next;
		close_fd(tmp);
		free_tab(tmp->arg);
		free(tmp);
	}
	free_tab(data->env);
	close(data->save_in);
	close(data->save_out);
	free(data);
}
