#include "get_next_line.h"

char	*create_newline(char ***line, char *x)
{
	int		i;
	int		y;
	char	*new_line;

	i = 0;
	while (x[i] && !is_n(x[i]))
		i++;
	y = 0;
	while ((**line)[y])
		y++;
	new_line = malloc(sizeof(char) * (y + 1));
	if (!(new_line))
		return (NULL);
	y = -1;
	while ((**line)[++y])
		new_line[y] = (**line)[y];
	new_line[y] = '\0';
	return (new_line);
}

int	assign(char ***line, char *x)
{
	int		i;
	int		y;
	char	*new_line;

	new_line = create_newline(line, x);
	if (!(new_line))
		return (ERROR);
	i = 0;
	while (x[i] && !is_n(x[i]))
		i++;
	y = 0;
	while ((**line)[y])
		y++;
	free(**line);
	**line = malloc(sizeof(char) * (y + i + 1));
	if (!(**line))
		return (ERROR);
	return (assign_new_line(line, x, new_line));
}

int	recurs(int fd, char **line)
{
	static char		x[BUFFER_SIZE + 1] = "";
	int				res;

	res = assign(&line, (char *)&(x));
	if (res == 0)
	{
		res = read(fd, x, BUFFER_SIZE);
		if (res == -1)
		{
			free(*line);
			*line = NULL;
			return (ERROR);
		}
		x[res] = '\0';
		if (res == 0)
			return (END);
		return (recurs(fd, line));
	}
	else
		decaler(res, (char *)&x);
	return (OK);
}

int	get_next_line(int fd, char **line)
{
	int	res;

	if (fd < 0 || fd > 180 || !line || BUFFER_SIZE < 1)
		return (ERROR);
	*line = malloc(sizeof(char) * (1));
	if (!(*line))
		return (ERROR);
	*line[0] = '\0';
	res = recurs(fd, line);
	if (res == END)
		return (END);
	return (res);
}
