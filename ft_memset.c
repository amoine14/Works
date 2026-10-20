/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 08:56:02 by username          #+#    #+#             */
/*   Updated: 2026/10/20 09:38:18 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	return (s);
}

// void	main(int argc, char **argv)
// {
// 	char	*str;

// 	str = argv[1];
// 	printf("avant : %s\n", str);
// 	ft_memset(str, 88, 4);
// 	printf("apres : %s\n", str);
// }
