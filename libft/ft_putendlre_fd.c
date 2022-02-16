#include "libft.h"

int	ft_putendlre_fd(char *s, int fd, int ret)
{
	char *tmp;

	tmp = ft_strjoin(s, "\n");
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
    return (ret);
}
