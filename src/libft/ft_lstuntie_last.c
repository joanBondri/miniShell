#include "libft.h"

t_list	*ft_lstuntie_last(t_list *list)
{
	t_list	*buff;

	if (!list || !(list->next))
		return (NULL);
	buff = ft_lstuntie_last(list->next);
	if (!buff)
	{
		buff = list->next;
		list->next = NULL;
	}
	return (buff);
}
