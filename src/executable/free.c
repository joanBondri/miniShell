/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:32:49 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/17 05:04:30 by jbondri          ###   ########.fr       */
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
	t_data	*data;

	data = get_data(NULL);
	change_mind("yes", true);
	free_tab(data->env);
	close(data->save_in);
	close(data->save_out);
	free(data);
}

void	free_all_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->prev;
	}
	cmd = tmp;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_tab(tmp->arg);
		if (tmp->infile != -1)
			close(tmp->infile);
		if (tmp->outfile != -1)
			close(tmp->outfile);
		free(tmp->path);
		free(tmp);
	}
}

void	free_data_cmd2(t_data *data)
{
	change_mind("yes", true);
	free_tab(data->env);
	close(data->save_in);
	close(data->save_out);
	free(data);
}
