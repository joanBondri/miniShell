#include "get_next_line.h"

int	is_n(char c)
{
	if (c == '\n')
		return (1);
	return (0);
}

void	decaler(int res, char *x)
{
	int	i;

	i = -1;
	while (++i < BUFFER_SIZE + 1 - res)
		x[i] = x[i + res];
	while (++i < BUFFER_SIZE + 1)
		x[i] = '\0';
}

int	assign_new_line(char ***line, char *x, char *new_line)
{
	int	i;
	int	y;

	y = -1;
	while (new_line[++y])
		(**line)[y] = new_line[y];
	free(new_line);
	i = -1;
	while (x[++i] && !is_n(x[i]))
		(**line)[y + i] = x[i];
	(**line)[y + i] = '\0';
	if (is_n(x[i]))
		return (i + 1);
	return (0);
}
