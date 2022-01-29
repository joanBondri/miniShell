#include "pips.h"

t_list	**add_lst_malloc(void *mem)
{
	static	t_lst	*one = NULL;

	if (mem)
		ft_lstadd_front(&one, ft_lstnew(mem));
	return (&one);
}

void	*ft_malloc_conditional(size_t len)
{
	void	*mem;

	mem = malloc(len);
	if (mem)
		add_lst_malloc(mem);
	return (mem);
}

void	free_all_lst_malloc(void)
{
	t_lst	**all;

	all = add_lst_malloc(NULL);
	ft_lst_clear(all, free);
}

void	ft_nothing(void *mem)
{
	(void)mem;
	return ;
}

void	free_lst(void)
{
	t_lst	**all;

	all = add_lst_malloc(NULL);
	ft_lst_clear(all, ft_nothing);
}
