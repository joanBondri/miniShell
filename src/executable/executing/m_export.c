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

void	print_export_error(char *str)
{
	print_free(ft_strjoin3("minishell: export: « ", str,
			" » : identifiant non valable\n"), STDERR_FILENO);
}

void	print_tab(t_data *data, int *tab, int lenght)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < lenght)
	{
		j = 0;
		while (j < lenght)
		{
			if (tab[j] == i)
			{
				tab[j] = -1;
				print_free(ft_strjoin3("export ",
						data->env[j], "\n"), STDOUT_FILENO);
				i = -1;
				break ;
			}
			j++;
		}
		i++;
	}
	free(tab);
}

void	iteration_export(int *iter, int lenght, int *tab, t_data *data)
{
	iter[0] = 0;
	while (iter[0] < lenght)
	{
		iter[1] = 0;
		while (iter[1] < lenght)
		{
			if (ft_strcmp(data->env[iter[0]], data->env[iter[1]]) > 0)
				tab[iter[0]] = tab[iter[0]] + 1;
			iter[1]++;
		}
		iter[0]++;
	}
	print_tab(data, tab, lenght);
}

void	print_export_env(t_data *data)
{
	int	*tab;
	int	lenght;
	int	iter[3];

	iter[0] = 0;
	while (data->env[iter[0]])
		iter[0]++;
	lenght = iter[0];
	tab = malloc(sizeof(int) * lenght);
	if (!tab)
		ft_error(MALLOC);
	iter[0] = 0;
	while (iter[0] < lenght)
	{
		tab[iter[0]] = 0;
		iter[0]++;
	}
	iteration_export(iter, lenght, tab, data);
}

int	m_export(t_data *data, t_cmd *cmd)
{
	char	*tmp;
	char	**env_val;
	char	*tab_cell;
	int		i;
	int		return_status;

	i = 1;
	return_status = 0;
	if (!cmd->arg[1])
	{
		if (data->env == NULL)
			return (1);
		print_export_env(data);
		return (0);
	}
	while (cmd->arg[i])
	{
		env_val = ft_split2(cmd->arg[i], '=');
		if (!env_val[1])//uselss
			tab_cell = ft_strdup("");
		else
		{
			ft_trim(env_val[1], '"');
			ft_trim(env_val[1], '\'');
			tab_cell = env_val[1];
			if (is_correct_export(env_val, tab_cell, cmd->arg[i]) == 0)
			{
				if (find_index_env(data, env_val[0]) >= 0)
				{
					tmp = data->env[find_index_env(data, env_val[0])];
					data->env[find_index_env(data, env_val[0])]
						= ft_strjoin3(env_val[0], "=", env_val[1]);
					free(tmp);
				}
				else
				{
					return_status = add_var_tab(data, ft_strjoin3(env_val[0], "=", env_val[1]));
					if (return_status == -1)
						return_status = 1;
					else
						return_status = 0;
				}
			}
			else
			{
				print_export_error(cmd->arg[i]);
				return_status = 1;
			}
		}
		if (!env_val[1])
			free(tab_cell);
		free_tab(env_val);
		i++;
	}
	return (return_status);
}
