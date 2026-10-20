/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 09:28:32 by username          #+#    #+#             */
/*   Updated: 2026/10/20 13:24:13 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;
	size_t				i;

	pdest = (unsigned char *) dest;
	psrc = (const unsigned char *) src;
	i = 0;
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}

// int	main(int argc, char **argv)
// {
// 	const char	*src;
// 	char		*dest;
// 	size_t		n;

// 	argc = argc;
// 	src = argv[1];
// 	dest = argv[2];
// 	n = 5;
// 	printf("AVANT | %s | %s\n", src, dest);
// 	ft_memcpy(dest, src, n);
// 	printf("APRES | %s | %s\n", src, dest);
// 	return (0);
// }
