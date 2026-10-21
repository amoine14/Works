/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 10:51:23 by username          #+#    #+#             */
/*   Updated: 2026/10/21 11:08:17 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lenp;
	size_t	lens;
	size_t	i;
	char	*str;

	lenp = 0;
	lens = 0;
	i = 0;
	while (s1[lenp])
		lenp++;
	while (s2[lens])
		lens++;
	printf("Len s1 : %ld | Len s2 : %ld\n", lens, lenp);
	str = malloc(sizeof(char) * (lens + lenp) + 1);
	if (str == NULL)
		return (NULL);
	while (i < lenp)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < lens)
	{
		str[i + lenp] = s2[i];
		i++;
	}
	str[i + lenp] = '\0';
	return (str);
}

// int	main(int argc, char **argv)
// {
// 	char	*result;
// 	size_t	len1;
// 	size_t	len2;
// 	size_t	total;

// 	if (argc != 3)
// 		return (1);
// 	len1 = strlen(argv[1]);
// 	len2 = strlen(argv[2]);
// 	total = len1 + len2 + 1;
// 	result = ft_strjoin(argv[1], argv[2]);
// 	if (result == NULL)
// 	{
// 		printf("Erreur d'allocation\n");
// 		return (1);
// 	}
// 	printf("Chaine 1 : %s (%zu)\n", argv[1], len1);
// 	printf("Chaine 2 : %s (%zu)\n", argv[2], len2);
// 	printf("Resultat : %s\n", result);
// 	printf("Longueur resultat : %zu\n", strlen(result) + 1);
// 	printf("Taille malloc attendue : %zu octets\n", total);
// 	free(result);
// 	return (0);
// }
