/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:05:26 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/22 14:33:32 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

bool	change_mind(char *change, bool bo)
{
	static bool		yop = false;
	bool			buff;

	if (change && !ft_strncmp(change, "yes", ft_strlen(change)))
	{
		buff = yop;
		yop = bo;
		return (buff);
	}
	return (yop);
}

int	find_var_par(char *prin, char **res)
{
	int		i;

	i = -1;
	while (prin[++i])
	{
		if (prin[i] == '}')
			break ;
	}
	if (i == 2)
		*res = NULL;
	else
		*res = malloc(sizeof(char) * (i - 2));
	if (!*res)
	{
		ft_putstr_fd("error_malloc\n", 2);
		change_mind("yes", true);
		return (-1);
	}
	ft_strlcpy(*res, prin + 2, i - 1);
	return (i + 1);
}

int	parse_varenv(char **start, char *prin, size_t *s)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	*s = 1;
	*start = NULL;
	while (prin[++j])
	{
		if (j == 1 && ft_isdigit(prin[j]))
		{
			*start = prin + j;
			i = 1;
			break ;
		}
		if (!ft_isalnum(prin[j]) && prin[j] != '_')
			break ;
		if (!(*start))
			*start = prin + j;
		else
			(*s)++;
		i++;
	}
	return (i);
}

int	find_variable_in_str(char *prin, char **res)
{
	char	*start;
	int		i;
	size_t	s;

	if (prin[0] != '$')
		return (-1);
	if (prin[1] && prin[1] == '{')
		return (find_var_par(prin, res));
	i = parse_varenv(&start, prin, &s);
	if (!start)
		return (-1);
	*res = malloc(sizeof(char) * (s + 1));
	if (!*res)
	{
		ft_putstr_fd("error_malloc\n", 2);
		return_value(1, 0);
		change_mind("yes", true);
		return (-1);
	}
	ft_strlcpy(*res, prin + 1, s + 1);
	return (i + 1);
}
