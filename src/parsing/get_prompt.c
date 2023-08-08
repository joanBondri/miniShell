/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 05:18:23 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/25 20:12:30 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

char	*ft_loop_strchr(const char *str, char *c)
{
	char	*res;
	int		i;

	i = -1;
	if (!str || !c)
		return (NULL);
	while (c[++i])
	{
		res = ft_strchr(str, c[i]);
		if (res == NULL)
			break ;
	}
	return (res);
}

void	final_free(t_data *data)
{
	free_all_lst_malloc();
	free_tab(data->env);
	free(data);
}

void	come_back_prompt(t_data **data)
{
	char	*str;
	char	**env;

	while (true)
	{
		signal(SIGINT, handler_int);
		signal(SIGQUIT, SIG_IGN);
		env = (*data)->env;
		(**data) = (t_data){0};
		(*data)->env = env;
		str = readline("minishell$ ");
		if (!str)
			break ;
		if (!ft_loop_strchr(" \t\v\f", str))
			add_history(str);
		if (!ft_loop_strchr(" \t\v\f", str))
			parser_director(str, data);
		free_all_lst_malloc();
		if (str)
			free(str);
		str = NULL;
	}
	final_free(*data);
	exit(ft_putendlre_fd("exit", STDOUT_FILENO, 0));
}
