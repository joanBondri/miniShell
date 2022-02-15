/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:27:37 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/10 16:34:22 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	export_modif_tab(t_data *data, char **env_val)
{
	char	*tmp;
	int		return_status;

	return_status = 0;
	if (find_index_env(data, env_val[0]) >= 0)
	{
		tmp = data->env[find_index_env(data, env_val[0])];
		data->env[find_index_env(data, env_val[0])]
			= ft_strjoin3(env_val[0], "=", env_val[1]);
		free(tmp);
	}
	else
	{
		return_status = add_var_tab(data,
				ft_strjoin3(env_val[0], "=", env_val[1]));
		if (return_status == -1)
			return_status = 1;
		else
			return_status = 0;
	}
	return (return_status);
}

int	loop_export(t_data *data, t_cmd *cmd, int i)
{
	char	**env_val;
	char	*tab_cell;
	int		return_status;

	return_status = 0;
	env_val = ft_split2(cmd->arg[i], '=');
	if (is_valid_var(env_val[0]) == 1)
		return (print_export_error(env_val[0]));
	if (ft_strfind(cmd->arg[i], '=') == -1)
		return (0);
	if (!env_val[1])
		tab_cell = ft_strdup("");
	else
	{
		ft_trim(env_val[1], '"');
		ft_trim(env_val[1], '\'');
		tab_cell = env_val[1];
		if (is_correct_export(env_val, tab_cell, cmd->arg[i]) == 0)
			return_status = export_modif_tab(data, env_val);
		else
			return_status = print_export_error(cmd->arg[i]);
	}
	if (!env_val[1])
		free(tab_cell);
	free_tab(env_val);
	return (return_status);
}

int	m_export(t_data *data, t_cmd *cmd)
{
	int		i;
	int		secure;
	int		return_status;

	i = 1;
	return_status = 0;
	secure = 0;
	if (!cmd->arg[1])
	{
		if (data->env == NULL)
			return (1);
		print_export_env(data);
		return (0);
	}
	while (cmd->arg[i])
	{
		return_status = loop_export(data, cmd, i);
		if (return_status > 0)
			secure = 1;
		i++;
	}
	return (secure);
}
