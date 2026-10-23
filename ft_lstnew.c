/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 09:23:07 by username          #+#    #+#             */
/*   Updated: 2026/10/23 12:50:54 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// int	main(void)
// {
// 	t_list	*node;
// 	int		n;

// 	n = 42;
// 	node = ft_lstnew(&n);
// 	if (!node)
// 		return (1);
// 	printf("Adresse du maillon : %p\n", (void *) node);
// 	printf("Content (valeur)  : %d\n", *(int *) node->content);
// 	printf("Content (adresse) : %p\n", node->content);
// 	printf("Next              : %p\n", (void *) node->next);
// 	free(node);
// 	return (0);
// }
