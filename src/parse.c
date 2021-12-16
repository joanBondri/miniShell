#include "minishell.h"

t_data	parse(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	data->env = list_env(env);
}
