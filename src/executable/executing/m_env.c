/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:15:33 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/10 14:15:35 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	print_env_error(char *str)
{
	print_free(ft_strjoin3("env: «", str,
			"»: Aucun fichier ou dossier de ce type\n"), STDERR_FILENO);
}

void	print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strfind(data->env[i], '=') != -1)
			ft_putendl_fd(data->env[i], STDOUT_FILENO);
		i++;
	}
}

int	m_env(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 1;
	(void)cmd;
	if (!data->env)
		return (1);
	while (cmd->arg[i])
	{
		if (ft_strfind(cmd->arg[i], '=') == -1)
		{
			print_env_error(cmd->arg[i]);
			return (127);
		}
		i++;
	}
	print_env(data);
	i = 1;
	while (cmd->arg[i])
		ft_putendl_fd(cmd->arg[i++], STDOUT_FILENO);
	return (0);
}
