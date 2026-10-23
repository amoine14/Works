/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 15:57:56 by username          #+#    #+#             */
/*   Updated: 2026/10/23 17:59:46 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*copie;
	t_list	*node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	copie = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
			return (ft_lstclear(&copie, del), NULL);
		node = ft_lstnew(content);
		if (!node)
		{
			del(content);
			ft_lstclear(&copie, del);
			return (NULL);
		}
		ft_lstadd_back(&copie, node);
		lst = lst->next;
	}
	return (copie);
}

// void	*double_value(void *content)
// {
// 	int	*result;

// 	result = malloc(sizeof(int));
// 	if (!result)
// 		return (NULL);
// 	*result = *(int *) content * 2;
// 	return (result);
// }

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*copie;
// 	t_list	*tmp;
// 	int		*value;
// 	int		i;

// 	lst = NULL;
// 	i = 1;
// 	while (i <= 5)
// 	{
// 		value = malloc(sizeof(int));
// 		if (!value)
// 		{
// 			ft_lstclear(&lst, free);
// 			return (1);
// 		}
// 		*value = i * 10;
// 		tmp = ft_lstnew(value);
// 		if (!tmp)
// 		{
// 			free(value);
// 			ft_lstclear(&lst, free);
// 			return (1);
// 		}
// 		ft_lstadd_back(&lst, tmp);
// 		i++;
// 	}
// 	copie = ft_lstmap(lst, double_value, free);
// 	if (!copie)
// 	{
// 		ft_lstclear(&lst, free);
// 		return (1);
// 	}
// 	printf("=== LISTE ORIGINALE ===\n");
// 	tmp = lst;
// 	while (tmp)
// 	{
// 		printf("%d\n", *(int *) tmp->content);
// 		tmp = tmp->next;
// 	}
// 	printf("\n=== LISTE TRANSFORMEE ===\n");
// 	tmp = copie;
// 	while (tmp)
// 	{
// 		printf("%d\n", *(int *) tmp->content);
// 		tmp = tmp->next;
// 	}
// 	printf("\nTailles : original=%d, copie=%d\n",
// 		ft_lstsize(lst), ft_lstsize(copie));
// 	ft_lstclear(&lst, free);
// 	ft_lstclear(&copie, free);
// 	return (0);
// }
