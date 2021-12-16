/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <joan.bondri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:25:04 by jbondri           #+#    #+#             */
/*   Updated: 2020/11/18 16:25:07 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*back;

	if (alst == NULL || new == NULL)
		return ;
	back = ft_lstlast(*alst);
	if (back == NULL)
		return (ft_lstadd_front(alst, new));
	back->next = new;
	new->next = NULL;
	return ;
}
