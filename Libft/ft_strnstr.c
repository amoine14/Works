/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 16:55:03 by username          #+#    #+#             */
/*   Updated: 2026/10/21 09:22:39 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *) big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && j + i < len)
		{
			j++;
			if (!(little[j]))
				return ((char *)(big + i));
		}
		i++;
	}
	return ((NULL));
}

// int	main(int argc, char **argv)
// {
// 	char	*original;
// 	char	*mine;
// 	size_t	len;

// 	if (argc != 4)
// 		return (1);
// 	len = (size_t) atoi(argv[3]);
// 	original = strnstr(argv[1], argv[2], len);
// 	mine = ft_strnstr(argv[1], argv[2], len);
// 	if (original == NULL)
// 		printf("Original : NULL\n");
// 	else
// 		printf("Original : %s\n", original);
// 	if (mine == NULL)
// 		printf("Ma fonction : NULL\n");
// 	else
// 		printf("Ma fonction : %s\n", mine);
// 	if (original == mine)
// 		printf("OK\n");
// 	else
// 		printf("KO\n");
// 	return (0);
// }
