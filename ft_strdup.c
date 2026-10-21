/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 10:03:38 by username          #+#    #+#             */
/*   Updated: 2026/10/21 10:40:56 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include <stddef.h>

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*str;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	str = malloc(sizeof(char)*len + 1);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// int	main(int argc, char **argv)
// {
// 	char	*original;
// 	char	*mine;

// 	if (argc != 2)
// 		return (1);
// 	original = strdup(argv[1]);
// 	mine = ft_strdup(argv[1]);
// 	if (!original || !mine)
// 	{
// 		printf("Erreur d'allocation\n");
// 		free(original);
// 		free(mine);
// 		return (1);
// 	}
// 	printf("Original : %s\n", original);
// 	printf("Ma fonction : %s\n", mine);
// 	if (strcmp(original, mine) == 0)
// 		printf("OK\n");
// 	else
// 		printf("KO\n");
// 	free(original);
// 	free(mine);
// 	return (0);
// }
