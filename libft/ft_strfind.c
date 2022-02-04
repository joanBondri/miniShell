#include "libft.h"
#include <stdio.h>

int ft_strfind(char *str, char c)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (!str)
		return (-1);
	while (str[len])
		len++;
	while (str[i] && str[i] != c)
		i++;
	if (i != len)
		return (i);
	else
		return (-1);
}
