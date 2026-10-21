/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 10:28:33 by username          #+#    #+#             */
/*   Updated: 2026/10/21 15:03:33 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;
	size_t	i;

	slen = ft_strlen(s);
	if (start >= slen)
		len = 0;
	else if (len > slen - start)
		len = slen - start;
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

// int	main(int argc, char **argv)
// {
// 	char	*result;
// 	size_t	start;
// 	size_t	len;

// 	if (argc != 4)
// 		return (1);
// 	start = (size_t) atoi(argv[2]);
// 	len = (size_t) atoi(argv[3]);
// 	result = ft_substr(argv[1], start, len);
// 	if (result == NULL)
// 	{
// 		printf("Erreur d'allocation\n");
// 		return (1);
// 	}
// 	printf("Resultat : %s\n", result);
// 	free(result);
// 	return (0);
// }
