#include "pip.h"

void	know_your_token(char *s, t_data *dt)
{
	t_token		t;
	int			i = 0;

	while (s[i])
	{
		t = (t_token){0};
		next_token(s + i, &t, dt);
		printf("whats poppin, status = %i, substatus = %i, copy = %s, t_len = %i\n", t.status, t.sub_status, t.copy, t.length);
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

	i = 0;
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	*data = (t_data){0};
	//a modifier avec ce que xcahhhhhhhhal a fait
	while (env[i])
		i++;
    data->env = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (env[i])
    {
        data->env[i] = ft_strdup(env[i]);
        i++;
    }
	data->env[i] = NULL;
	come_back_prompt(&data);
	return (data);
}
