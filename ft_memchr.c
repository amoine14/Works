/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:49:57 by username          #+#    #+#             */
/*   Updated: 2026/10/21 11:57:33 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ps;
	size_t				i;

	i = 0;
	ps = (const unsigned char *) s;
	while (i < n && ps[i] != (unsigned char) c)
		i++;
	if (ps[i] == (unsigned char) c)
		return ((void *)(s + i));
	else
		return (NULL);
}

// int	main(int argc, char **argv)
// {
// 	void	*result_ft;
// 	void	*result_std;
// 	size_t	n;
// 	int		c;

// 	if (argc != 4)
// 	{
// 		printf("Usage : ./a.out chaine caractere n\n");
// 		return (1);
// 	}
// 	c = (unsigned char) argv[2][0];
// 	n = (size_t) atoi(argv[3]);
// 	if (n > strlen(argv[1]) + 1)
// 		return (1);
// 	result_ft = ft_memchr(argv[1], c, n);
// 	result_std = memchr(argv[1], c, n);
// 	printf("ft_memchr : %p\n", result_ft);
// 	printf("memchr    : %p\n", result_std);
// 	if (result_ft)
// 		printf("Caractere trouve : %c\n", *(char *) result_ft);
// 	return (0);
// }
