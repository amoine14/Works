/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 13:14:17 by username          #+#    #+#             */
/*   Updated: 2026/10/23 13:21:05 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*last;
// 	t_list	*tmp;

// 	lst = NULL;
// 	last = ft_lstlast(lst);
// 	printf("Liste vide : %p (attendu : NULL)\n", (void *) last);
// 	ft_lstadd_front(&lst, ft_lstnew("A"));
// 	last = ft_lstlast(lst);
// 	printf("1 maillon  : %s (attendu : A)\n", (char *) last->content);
// 	ft_lstadd_front(&lst, ft_lstnew("B"));
// 	ft_lstadd_front(&lst, ft_lstnew("C"));
// 	last = ft_lstlast(lst);
// 	printf("3 maillons : %s (attendu : A)\n", (char *) last->content);
// 	printf("Next du dernier : %p (attendu : NULL)\n",
// 		(void *) last->next);
// 	while (lst)
// 	{
// 		tmp = lst->next;
// 		free(lst);
// 		lst = tmp;
// 	}
// 	return (0);
// }
