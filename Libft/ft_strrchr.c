/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 16:47:41 by username          #+#    #+#             */
/*   Updated: 2026/10/20 16:54:40 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	while (i > 0 && s[i] != c)
	{
		i--;
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
// 	original = strrchr(argv[1], argv[2][0]);
// 	mine = ft_strrchr(argv[1], argv[2][0]);
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
