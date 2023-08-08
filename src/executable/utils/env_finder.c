/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:44:13 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/17 23:12:35 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_valid_var(char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "") == 0)
		return (1);
	while (str[i])
	{
		if (i != 0)
			if (((ft_isalpha(str[i]) == 0) && (ft_isdigit(str[i]) == 0))
				&& (str[i] != '_'))
				return (1);
		if (i == 0)
			if ((ft_isalpha(str[i]) == 0) && (str[i] != '_'))
				return (1);
		i++;
	}
	return (0);
}

int	is_correct_export(char **env_val, char *tab_cell, char *str)
{
	if (!env_val || !tab_cell)
		return (1);
	if (is_valid_var(env_val[0]) == 1)
		return (1);
	if (ft_strfind(str, '=') == -1)
		return (1);
	return (0);
}

char	*find_env(char *var, t_data *data)
{
	int		index;
	char	*tmp;

	index = find_index_env(data, var);
	if (index == -1)
		return (NULL);
	tmp = data->env[index];
	tmp = tmp + (ft_strlen(var) + 1);
	return (ft_strdup(tmp));
}

int	find_index_env(t_data *data, char *str)
{
	int	i;

	i = 0;
	if (!data->env)
		return (-2);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], str, ft_strlen(str)) == 0
			&& (data->env[i][ft_strlen(str)] == '='
			|| data->env[i][ft_strlen(str)] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	change_val_var(t_data *data, char *str, int i)
{
	free(data->env[i]);
	data->env[i] = str;
	return (1);
}
