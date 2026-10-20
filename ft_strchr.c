/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 15:59:28 by username          #+#    #+#             */
/*   Updated: 2026/10/20 16:50:39 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	if (s[i] == c)
		return ((void *) & s[i]);
	return (NULL);
}

// int	main(int argc, char **argv)
// {
// 	char	*original;
// 	char	*mine;

// 	if (argc != 3)
// 		return (1);
// 	original = strchr(argv[1], argv[2][0]);
// 	mine = ft_strchr(argv[1], argv[2][0]);
// 	if (original == NULL)
// 		printf("Original : NULL\n");
// 	else
// 		printf("Original : %s\n", original);
// 	if (mine == NULL)
// 		printf("Ma fonction : NULL\n");
// 	else
// 		printf("Ma fonction : %s\n", mine);
// 	return (0);
// }
