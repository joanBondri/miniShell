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

int	export_modif_tab(t_data *data, char **env_val, char *tab_cell)
{
	char	*tmp;
	int		return_status;

	return_status = 0;
	if (find_index_env(data, env_val[0]) >= 0)
	{
		tmp = data->env[find_index_env(data, env_val[0])];
		data->env[find_index_env(data, env_val[0])]
			= ft_strjoin3(env_val[0], "=", tab_cell);
		free(tmp);
	}
	else
	{
		tmp = ft_strjoin3(env_val[0], "=", tab_cell);
		return_status = add_var_tab(data, tmp);
		if (return_status == -1)
			return_status = 1;
		else
			return_status = 0;
		free(tmp);
	}
	return (return_status);
}

int	export_only_var(t_data *data, char	**env_val)
{
	int	return_status;

	return_status = 0;
	if (is_valid_var(env_val[0]) == 1)
	{
		print_export_error(env_val[0]);
		free_tab(env_val);
		return (1);
	}
	if (find_index_env(data, env_val[0]) >= 0)
	{
		free_tab(env_val);
		return (0);
	}
	else
	{
		return_status = add_var_tab(data, env_val[0]);
		free_tab(env_val);
		if (return_status == -1)
			return (ft_putendlre_fd("minishell: export: Can't export variable",
					STDERR_FILENO, 1));
		else
			return (0);
	}
}

int	export_join_tab(t_data *data, char **env_val, char *tab_cell)
{
	char	*tmp;
	int		return_status;

	return_status = 0;
	if (find_index_env(data, env_val[0]) >= 0
		&& ft_strfind(data->env[find_index_env(data, env_val[0])], '=') != -1)
	{
		tmp = data->env[find_index_env(data, env_val[0])];
		data->env[find_index_env(data, env_val[0])]
			= ft_strjoin(tmp, tab_cell);
		free(tmp);
	}
	else if (find_index_env(data, env_val[0]) >= 0
		&& ft_strfind(data->env[find_index_env(data, env_val[0])], '=') == -1)
	{
		tmp = data->env[find_index_env(data, env_val[0])];
		data->env[find_index_env(data, env_val[0])]
			= ft_strjoin3(env_val[0], "=", tab_cell);
		free(tmp);
	}
	else
		return_status = case_not_existing(data, env_val, tab_cell);
	return (return_status);
}

int	loop_export(t_data *data, t_cmd *cmd, int i)
{
	char	**env_val;
	char	*tab_cell;
	int		return_status;

	return_status = 0;
	env_val = ft_split2(cmd->arg[i], '=');
	if (!env_val[0])
		return (print_export_error_free("=", env_val));
	if (ft_strfind(cmd->arg[i], '=') == -1)
		return (export_only_var(data, env_val));
	if (!env_val[1])
		tab_cell = ft_strdup("");
	else
		tab_cell = env_val[1];
	if (is_strjoin(env_val, tab_cell, cmd->arg[i], cmd) == 0)
		return_status = export_join_tab(data, env_val, tab_cell);
	else if (is_correct_export(env_val, tab_cell, cmd->arg[i]) == 0)
		return_status = export_modif_tab(data, env_val, tab_cell);
	else
		return_status = print_export_error(cmd->arg[i]);
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
