#include "pips.h"

int	find_var_par(char *prin, char *res)
{
	int		i;

	i = 1;
	while (prin[++i])
	{
		if (prin[i] == '}')
			break ;
	}
	if (i == 2)
		res = NULL;
	else
		res = malloc(sizeof(char) * (i - 2));
	if (!res)
		ft_exit("error_malloc\n");
	ft_strlcpy(res, prin + 2, i - 2);
	return (i - 2);
}

int	find_variable_in_str(char *prin, char *res)
{
	int		i;
	int		j;
	char	*start;
	size_t	s;

	i = 0;
	j = -1;
	s = 1;
	start = NULL;
	if (prin[++j] != '$')
		return (-1);
	while (prin[++j])
	{
		if (j == 1 && prin[j] == '{')
			return (find_var_par(prin, res));
		if (j == 1 && is_digit(prin[j]))
			break ;
		if (!ft_strchr("1234567890_qwertyuiopasdfghj
					klzxcvbnQWERTYUIOPASDFGHJKLZXCVB", prin[j]))
			break ;
		if (!start)
			start = prin + j;
		else
			s++;
		i++;
	}
	if (!start)
		return (-1);
	res = malloc(sizeof(char) * (s + 1));
	if (!res)
		ft_exit("error with malloc\n");
	ft_strlcpy(res, prin, s);
	return (i);
}

char	*get_variable_first_time(char *val, int msg, t_data *dt)
{
	char	*str;
	char	*str_2;
	int		state;
	int		i;

	state = 0;
	str = find_env(var, dt);
	if (!str)
		ft_exit("Malloc error\n");
	if (msg == MSDQUOTES)
		return (str);
	if (ft_strlen(str) == 0)
		;
	if (ft_strchr(" \t\n\f\v", str[0]))
	{
		free(str);
		return (NULL);
	}
	if (ft_strchr(" \t\n\f\v", str[ft_strlen(str)]))
		state = 2;
	if (state == 0)
		return (str);
	i = 0;
	while (ft_strchr(" \t\n\f\v", str[i]))
		i++;
	str_2 = ft_strdup(str);
	
	if (!str_2[0])
		return (str_2);
	i = 0;
	while (str_2[i] && !ft_strchr(" \t\n\f\v", str_2[i]))
		i++;
	str_2[i + 1] = 0;
	return (str_2);
}

int		expand_variable(char *prin, int ind, char *res, t_data *dt)
{
	bool	q;
	bool	dq;
	int		i;
	char	*val;

	i = -1;
	q = false;
	dq = false;
	if (!prin || ind < 0 || !h)
		return (-1);
	if (prin[ind] == '$')
	{
		if (prin[ind])
		while (prin[++i] && i < ind)
		{
			if (prin[i] == '\'' && dq == false)
				q = !q;
			if (prin[i] == '"' && q == false)
				dq = !dq;
		}
		if (q)
			return (-1);
		i = find_variable_in_str(prin + ind, val);
		if (!val)
			return (-1);
		if (dq)
			res = get_value(val, MSDQUOTES, dt);
		else
			res = get_value(val, MSNOTHING, dt);
		return (i);
	}
	return (-1);
}

void	find_n_replace(char *s,
		(bool f)(char *prin, int yop, char *rep, int *hwmny), t_data *dt)
{
	int		i;
	char	*res;
	int		len;

	i = -1;
	while (s[++i])
	{
		if (res)
		{
			free(res);
			res = NULL;
		}
		if (f(s, i, res, &len))
			replace(s + i, len, res);
	}
}

char	*quotes_and_variable(char *s, t_data *data)
{
	find_n_replace(s, &expand_variable, data);
}
