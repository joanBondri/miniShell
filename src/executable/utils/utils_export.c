/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:17:38 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/15 13:22:17 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	print_export_error(char *str)
{
	print_free(ft_strjoin3("minishell: export: « ", str,
			" » : identifiant non valable\n"), STDERR_FILENO);
    return (1);
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
