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
	//	printf("whats poppin, status = %i, substatus = %i, copy = %s, t_len = %i\n", t.status, t.sub_status, t.copy, t.length);
		if (t.copy)
			free(t.copy);
		if (t.length == 0)
			break ;
		i += t.length;
	}
}

t_data	*parse(char **env)
{
	t_data	*data;
	int		i;
	int		compteur;
	char	*tmp;

	i = 0;
	compteur = 0;
	if (!env)
		return (NULL);
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	*data = (t_data){0};
	while (env[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			compteur = (int)ft_atoi((env[i] + 6), 0, 0, 1);
			compteur++;
			if (compteur >= 1000)
			{
				ft_putstr_fd("minishell: warning: shell level (", 2);
				ft_putnbr_fd(compteur, 2);
				ft_putendl_fd(") too high, resetting to 1", 2);
				compteur = 1;
			}
			if (compteur < 0)
				compteur = 0;
			tmp = ft_itoa(compteur);
			data->env[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
		}
		else
			data->env[i] = ft_strdup(env[i]);
		i++;
	}
	data->env[i] = NULL;
	if (find_index_env(data, "SHLVL=") == -1)
		add_var_tab(data, "SHLVL=1");
	come_back_prompt(&data);
	return (data);
}
