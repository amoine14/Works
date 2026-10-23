/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 14:45:20 by username          #+#    #+#             */
/*   Updated: 2026/10/23 15:37:52 by amoine           ###   ########.fr       */
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

// int	main(void)
// {
// 	t_list	*lst;

// 	lst = NULL;
// 	ft_lstclear(&lst, free);
// 	printf("Liste vide : %p (attendu : NULL)\n", (void *) lst);
// 	lst = ft_lstnew(ft_strdup("A"));
// 	ft_lstclear(&lst, free);
// 	printf("1 maillon  : %p (attendu : NULL)\n", (void *) lst);
// 	lst = ft_lstnew(ft_strdup("A"));
// 	ft_lstadd_front(&lst, ft_lstnew(ft_strdup("B")));
// 	ft_lstadd_front(&lst, ft_lstnew(ft_strdup("C")));
// 	printf("Avant clear : %d maillons\n", ft_lstsize(lst));
// 	ft_lstclear(&lst, free);
// 	printf("Après clear : %d maillons\n", ft_lstsize(lst));
// 	printf("lst après clear : %p (attendu : NULL)\n", (void *) lst);
// 	return (0);
// }
