/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 09:52:14 by username          #+#    #+#             */
/*   Updated: 2026/10/20 15:25:38 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;
	size_t				i;

	pdest = (unsigned char *) dest;
	psrc = (const unsigned char *) src;
	i = 0;
	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			pdest[i] = psrc[i];
			i--;
		}
	}
	else
	{
		while (i < n)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	return (dest);
}

int	main(int argc, char **argv)
{
	char	*str;
	size_t	n;

	argc = argc;
	str = argv[1];
	n = 3;
	printf("AVANT | %s\n", str);
	ft_memmove(str + 2, str, n);
	printf("APRES | %s\n", str);
	return (0);
}
