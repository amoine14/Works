/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 10:17:25 by username          #+#    #+#             */
/*   Updated: 2026/10/20 12:05:46 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = 0;
	while (src[srclen])
		srclen++;
	if (size >= 1)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}

// int	main(void)
// {
// 	char	dest1[20] = "XXXXXXXXXX";
// 	char	*src = "Bonjour";
// 	size_t	size = 20;
// 	size_t	ret1;

// 	ret1 = ft_strlcpy(dest1, src, size);
// 	printf("ft_strlcpy : %s | retour : %zu\n", dest1, ret1);
// 	return (0);
// }
