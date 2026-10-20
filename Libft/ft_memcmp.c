/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 12:19:58 by username          #+#    #+#             */
/*   Updated: 2026/10/20 12:27:40 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *) s1;
	p2 = (const unsigned char *) s2;
	i = 0;
	while (p1[i] && p1[i] == p2[i] && i < n)
		i++;
	return (p1[i] - p2[i]);
}

// int	main(int argc, char **argv)
// {
// 	size_t	n;
// 	int		result_ft;
// 	int		result_std;

// 	if (argc != 4)
// 	{
// 		printf("Usage : ./a.out str1 str2 n\n");
// 		return (1);
// 	}
// 	if (argv[3][0] == '-')
// 		return (1);
// 	n = (size_t) atoi(argv[3]);
// 	if (n > strlen(argv[1]) + 1
// 			|| n > strlen(argv[2]) + 1)
// 	{
// 		printf("Erreur : n depasse la taille d'une source\n");
// 		return (1);
// 	}
// 	result_ft = ft_memcmp(argv[1], argv[2], n);
// 	result_std = memcmp(argv[1], argv[2], n);
// 	printf("ft_memcmp : %d\n", result_ft);
// 	printf("memcmp    : %d\n", result_std);
// 	return (0);
// }
