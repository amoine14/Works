/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 10:17:22 by username          #+#    #+#             */
/*   Updated: 2026/10/20 11:28:22 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	destlen = 0;
	i = 0;
	while (destlen < size && dst[destlen])
		destlen++;
	while (src[i])
		i++;
	srclen = i;
	if (destlen == size)
		return (destlen + srclen);
	i = 0;
	while (src[i] && i < size - destlen - 1)
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int	main(int argc, char **argv)
// {
// 	char	dest[100];
// 	size_t	size;
// 	size_t	result;

// 	if (argc != 4)
// 		return (1);
// 	if (strlen(argv[1]) >= sizeof(dest))
// 		return (1);
// 	strcpy(dest, argv[1]);
// 	size = (size_t) atoi(argv[3]);
// 	if (size > sizeof(dest))
// 		return (1);
// 	result = ft_strlcat(dest, argv[2], size);
// 	printf("Destination : %s\n", dest);
// 	printf("Retour : %zu\n", result);
// 	return (0);
// }
