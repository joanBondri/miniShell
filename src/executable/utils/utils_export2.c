/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:25:09 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/21 11:46:05 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	print_export_error(char *str)
{
	print_free(ft_strjoin3("minishell: export: « ", str,
			" » : identifiant non valable\n"), STDERR_FILENO);
	return (1);
}

int	print_export_error_free(char *str, char **tab)
{
	free_tab(tab);
	print_free(ft_strjoin3("minishell: export: « ", str,
			" » : identifiant non valable\n"), STDERR_FILENO);
	return (1);
}

int	export_print_line(t_data *data, int j)
{
	int	i;

	i = 0;
	ft_putstr_fd("export ", STDOUT_FILENO);
	while (data->env[j][i] && data->env[j][i] != '=')
	{
		ft_putchar_fd(data->env[j][i], STDOUT_FILENO);
		i++;
	}
	ft_putstr_fd("=\"", STDOUT_FILENO);
	i++;
	while (data->env[j][i])
	{
		ft_putchar_fd(data->env[j][i], STDOUT_FILENO);
		i++;
	}
	ft_putstr_fd("\"\n", STDOUT_FILENO);
	return (0);
}

void	print_tab(t_data *data, int *tab, int lenght, int i)
{
	int	j;

	j = 0;
	while (i < lenght)
	{
		j = 0;
		while (j < lenght)
		{
			if (tab[j] == i)
			{
				tab[j] = -1;
				if (ft_strfind(data->env[j], '=') != -1)
					export_print_line(data, j);
				else
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
