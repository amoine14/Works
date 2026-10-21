/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 09:24:32 by username          #+#    #+#             */
/*   Updated: 2026/10/21 09:54:43 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*mem;
	size_t			i;
	unsigned char	*pmem;

	i = 0;
	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	pmem = (unsigned char *) mem;
	while (i < nmemb * size)
	{
		*(pmem + i) = 0;
		i++;
	}
	return (mem);
}

// int	main(int argc, char **argv)
// {
// 	unsigned char	*original;
// 	unsigned char	*mine;
// 	size_t			n;
// 	size_t			size;
// 	size_t			i;

// 	if (argc != 3)
// 		return (1);
// 	n = (size_t) atoi(argv[1]);
// 	size = (size_t) atoi(argv[2]);
// 	original = calloc(n, size);
// 	mine = ft_calloc(n, size);
// 	if (!original || !mine)
// 	{
// 		printf("Allocation echouee\n");
// 		free(original);
// 		free(mine);
// 		return (1);
// 	}
// 	i = 0;
// 	while (i < n * size)
// 	{
// 		if (original[i] != mine[i])
// 			printf("KO a l'octet %zu\n", i);
// 		i++;
// 	}
// 	printf("Tout est bon\n");
// 	free(original);
// 	free(mine);
// 	return (0);
// }
