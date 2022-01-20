#include "pips.h"


bool	expand_variable(char *prin, int ind, char *res, int *h)
{
	bool	q;
	bool	dq;
	int		i;
	char	*val;

	i = -1;
	q = false;
	dq = false;
	if (!prin || ind < 0 || !h)
		return (false);
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
			return (false);
		val = find_variable_in_str(prin + ind + 1);
		if (dq)
		{
			
		}
	}
	return (false);
}

void	find_n_replace(char *s,
		(bool f)(char *prin, int yop, char *rep, int *hwmny))
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

char	*quotes_and_variable(char *s)
{
	find_n_replace(s, &expand_variable);
}
