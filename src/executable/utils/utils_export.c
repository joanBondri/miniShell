/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:17:38 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/25 19:58:34 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_strjoin(char **env_val, char *tab_cell, char *str, t_cmd *cmd)
{
	char	*tmp;
	char	*tmp2;

	if (env_val[0][ft_strlen(env_val[0]) - 1] == '+')
	{
		tmp = env_val[0];
		env_val[0] = ft_strtrim(env_val[0], "+");
		if (!env_val[0])
			ft_exit_exec(ft_error(MALLOC), cmd);
		if (is_correct_export(env_val, tab_cell, str) == 0)
		{
			free(tmp);
			return (0);
		}
		tmp2 = env_val[0];
		env_val[0] = tmp;
		free(tmp2);
	}
	return (1);
}

int	case_not_existing(t_data *data, char **env_val, char *tab_cell)
{
	char	*tmp;
	int		return_status;

	tmp = ft_strjoin3(env_val[0], "=", tab_cell);
	return_status = add_var_tab(data, tmp);
	if (return_status == -1)
		return_status = 1;
	else
		return_status = 0;
	free(tmp);
	return (return_status);
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
	print_tab(data, tab, lenght, 0);
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
