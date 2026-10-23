/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 12:59:24 by username          #+#    #+#             */
/*   Updated: 2026/10/23 13:07:49 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

int	main(void)
{
	t_list	*lst;

	lst = NULL;
	printf("Liste vide : %d (attendu : 0)\n", ft_lstsize(lst));
	ft_lstadd_front(&lst, ft_lstnew("A"));
	printf("1 maillon  : %d (attendu : 1)\n", ft_lstsize(lst));
	ft_lstadd_front(&lst, ft_lstnew("B"));
	ft_lstadd_front(&lst, ft_lstnew("C"));
	printf("3 maillons : %d (attendu : 3)\n", ft_lstsize(lst));
	while (lst)
	{
		t_list	*tmp = lst->next;

		free(lst);
		lst = tmp;
	}
	return (0);
}
