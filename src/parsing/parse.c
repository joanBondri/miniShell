/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 04:31:10 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/25 20:17:20 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

void	know_your_token(char *s, t_data *dt)
{
	t_token		t;
	int			i;

	i = 0;
	while (s[i])
	{
		t = (t_token){0};
		next_token(s + i, &t, dt);
		if (t.copy)
			free(t.copy);
		if (t.length == 0)
			break ;
		i += t.length;
	}
}

int	print_message_shlvl(int compteur)
{
	ft_putstr_fd("minishell: warning: shell level (", 2);
	ft_putnbr_fd(compteur, 2);
	ft_putendl_fd(") too high, resetting to 1", 2);
	return (1);
}

void	manage_shlvl(char **env, t_data *data)
{
	int		i;
	int		compteur;
	char	*tmp;

	compteur = 0;
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			compteur = (int)ft_atoi((env[i] + 6), 0, 0, 1);
			compteur++;
			if (compteur >= 1000 && print_message_shlvl(compteur))
				compteur = 1;
			if (compteur < 0)
				compteur = 0;
			tmp = ft_itoa(compteur);
			data->env[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
		}
		else
			data->env[i] = ft_strdup(env[i]);
	}
	data->env[i] = NULL;
}

t_data	*parse(char **env)
{
	t_data	*data;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	*data = (t_data){0};
	while (env[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	manage_shlvl(env, data);
	if (find_index_env(data, "SHLVL") == -1)
		add_var_tab(data, "SHLVL=1");
	get_data(data);
	come_back_prompt(&data);
	return (data);
}
