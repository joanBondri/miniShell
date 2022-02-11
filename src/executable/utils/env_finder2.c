/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_finder2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:59:34 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/10 14:59:12 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	loop_env(t_data *data, char **tmp, int o)
{
	while (data->env[o] != NULL)
	{
		tmp[o] = ft_strdup(data->env[o]);
		if (!tmp[o])
		{
			free_tab(tmp);
			return (-1);
		}
		o++;
	}
	return (0);
}

int	add_var_tab(t_data *data, char *str)
{
	int		i;
	int		o;
	char	**tmp;

	o = 0;
	i = 0;
	while (data->env[i] != NULL)
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (loop_env(data, tmp, o) == -1)
		return (-1);
	tmp[o] = str;
	if (!tmp[o])
	{
		free_tab(tmp);
		return (-1);
	}
	tmp[++o] = NULL;
	free_tab(data->env);
	data->env = tmp;
	return (1);
}

int	put_val_tab(t_data *data, char *var, char *new)
{
	char	*tmp;

	tmp = ft_strjoin3(var, "=", new);
	if (!tmp)
		return (-1);
	if (find_index_env(data, var) == -1)
	{
		if (add_var_tab(data, tmp) == -1)
			return (-1);
	}
	else
	{
		if (change_val_var(data, tmp, find_index_env(data, var)) == -1)
			return (-1);
	}
	return (0);
	}
