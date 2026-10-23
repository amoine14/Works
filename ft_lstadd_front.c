/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 12:16:37 by username          #+#    #+#             */
/*   Updated: 2026/10/23 12:52:25 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*new;

// 	lst = ft_lstnew("A");
// 	new = ft_lstnew("B");
// 	if (!lst || !new)
// 	{
// 		free(lst);
// 		free(new);
// 		return (1);
// 	}
// 	printf("=== AVANT ===\n");
// 	printf("lst : %s (%p)\n", (char *) lst->content, (void *) lst);
// 	printf("new : %s (%p)\n", (char *) new->content, (void *) new);
// 	printf("\n=== AJOUT ===\n");
// 	ft_lstadd_front(&lst, new);
// 	printf("lst : %s (%p)\n", (char *) lst->content, (void *) lst);
// 	printf("new : %s (%p)\n", (char *) new->content, (void *) new);
// 	printf("lst->next : %s (%p)\n",
// 		(char *) lst->next->content, (void *) lst->next);
// 	free(lst->next);
// 	free(lst);
// 	return (0);
// }
