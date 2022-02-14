#include "libft.h"
#define LIMITEMAL 5

void	*ft_malloc_3434(size_t si)
{
	static	int	i = 0;

	i++;
	if (i < LIMITEMAL)
		return (malloc(si));
	return (NULL);
}
