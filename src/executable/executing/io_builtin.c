/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:23:21 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/22 18:38:03 by jbondri          ###   ########.fr       */
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
		ft_exit_child(ft_error(CLOSE), data);
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
		ft_exit_child(ft_error(DUP2), data);
	return (0);
}

int	is_builtin(char *str)
{
	int		i;
	char	*builtin_id[7];

	i = 0;
	builtin_id[CD] = "cd";
	builtin_id[ECHO] = "echo";
	builtin_id[ENV] = "env";
	builtin_id[EXIT] = "exit";
	builtin_id[EXPORT] = "export";
	builtin_id[PWD] = "pwd";
	builtin_id[UNSET] = "unset";
	while (i < 7)
	{
		if (ft_strcmp(str, builtin_id[i]) == 0)
		{
			return (1);
		}
		i++;
	}
	return (-1);
}

int	call_builtin(t_data *data, t_cmd *cmd, int i)
{
	int		(*builtin[7])(t_data *data, t_cmd *cmd);
	char	*builtin_id[7];

	builtin_id[CD] = "cd";
	builtin_id[ECHO] = "echo";
	builtin_id[ENV] = "env";
	builtin_id[EXIT] = "exit";
	builtin_id[EXPORT] = "export";
	builtin_id[PWD] = "pwd";
	builtin_id[UNSET] = "unset";
	builtin[CD] = m_cd;
	builtin[ECHO] = m_echo;
	builtin[ENV] = m_env;
	builtin[EXIT] = m_exit;
	builtin[EXPORT] = m_export;
	builtin[PWD] = m_pwd;
	builtin[UNSET] = m_unset;
	while (i < 7)
	{
		if (ft_strcmp(cmd->arg[0], builtin_id[i]) == 0)
			return ((*builtin[i])(data, cmd));
		i++;
	}
	return (-1);
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
