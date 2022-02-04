#include "pip.h"

t_list	**add_lst_malloc(void *mem)
{
	static	t_list	*one = NULL;

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
	t_list	**all;

	all = add_lst_malloc(NULL);
	ft_lstclear(all, free);
}

void	ft_nothing(void *mem)
{
	(void)mem;
	return ;
}

void	free_lst(void)
{
	t_list	**all;

	all = add_lst_malloc(NULL);
	ft_lstclear(all, ft_nothing);
}
//fonction en chantier qui va servr a eviter les doubles free
