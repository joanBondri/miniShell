#include "libft.h"

double	ft_sqrt(double number)
{
	double	res;
	double	buff;

	res = number / 2;
	buff = 0;
	while (res != buff)
	{
		buff = res;
		res = (number / buff + buff) / 2;
	}
	return (res);
}
