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

char	**loop_env(t_data *data, char **tmp, int *o, int i)
{
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		ft_exit_child(ft_error(MALLOC), data);
	while (data->env[*o] != NULL)
	{
		tmp[*o] = ft_strdup(data->env[*o]);
		if (!tmp[*o])
		{
			free_tab(tmp);
			return (NULL);
		}
		*o += 1;
	}
	return (tmp);
}

int	add_var_tab(t_data *data, char *str)
{
	int		i;
	int		o;
	char	**tmp;

	tmp = NULL;
	o = 0;
	i = 0;
	while (data->env[i] != NULL)
		i++;
	tmp = loop_env(data, tmp, &o, i);
	if (tmp == NULL)
		return (-1);
	tmp[o] = ft_strdup(str);
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

int	put_val_tab_existing(t_data *data, char *var, char *new)
{
	char	*tmp;

	tmp = ft_strjoin3(var, "=", new);
	if (!tmp)
		return (-1);
	if (find_index_env(data, var) == -1)
	{
		free(tmp);
		return (0);
	}
	if (change_val_var(data, tmp, find_index_env(data, var)) == -1)
	{
		free(tmp);
		return (-1);
	}
	return (0);
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
		{
			free(tmp);
			return (-1);
		}
	}
	else
	{
		if (change_val_var(data, tmp, find_index_env(data, var)) == -1)
		{
			free(tmp);
			return (-1);
		}
	}
	free(tmp);
	return (0);
}
