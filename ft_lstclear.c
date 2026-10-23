/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 14:45:20 by username          #+#    #+#             */
/*   Updated: 2026/10/23 23:17:36 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*nextl;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		nextl = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = nextl;
	}
	*lst = NULL;
}
