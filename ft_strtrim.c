/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 11:24:39 by username          #+#    #+#             */
/*   Updated: 2026/10/21 11:57:00 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (ft_substr(s1, start, end - start));
}

// int	main(int argc, char **argv)
// {
// 	char	*result;

// 	if (argc != 3)
// 		return (1);
// 	result = ft_strtrim(argv[1], argv[2]);
// 	if (result == NULL)
// 	{
// 		printf("Erreur d'allocation\n");
// 		return (1);
// 	}
// 	printf("Original : [%s]\n", argv[1]);
// 	printf("Set      : [%s]\n", argv[2]);
// 	printf("Resultat : [%s]\n", result);
// 	printf("Longueur : %zu\n", strlen(result));
// 	free(result);
// 	return (0);
// }
