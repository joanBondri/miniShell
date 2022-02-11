/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:33:29 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/10 15:02:51 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**fill_new_tab(t_data *data, int index, char **temp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (i == index)
		{
			j--;
		}
		if (i != index)
		{
			temp[j] = ft_strdup(data->env[i]);
			if (!temp[j])
			{
				free_tab(temp);
				return (NULL);
			}
		}
		i++;
		j++;
	}
	return (temp);
}

int	remove_var_tab(t_data *data, char *var)
{
	int		i;
	int		index_env;
	char	**temp;

	i = 0;
	index_env = find_index_env(data, var);
	if (index_env < 0)
		return (0);
	while (data->env[i])
		i++;
	temp = malloc(sizeof(char *) * i);
	if (!temp)
		ft_error(MALLOC);
	temp = fill_new_tab(data, index_env, temp);
	if (!temp)
		ft_error(MALLOC);
	temp[i - 1] = NULL;
	free_tab(data->env);
	data->env = temp;
	return (0);
}

void	print_error_unset(char *str)
{
	print_free(ft_strjoin3("minishell: unset: « ", str,
			" » : identifiant non valable\n"), STDERR_FILENO);
}

int	m_unset(t_data *data, t_cmd *cmd)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (cmd->arg[i])
	{
		if (is_valid_var(cmd->arg[i]) == 1)
		{
			print_error_unset(cmd->arg[i]);
			ret = 1;
		}
		else
			remove_var_tab(data, cmd->arg[i]);
		i++;
	}
	return (ret);
}
