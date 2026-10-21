/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 15:28:48 by username          #+#    #+#             */
/*   Updated: 2026/10/21 17:13:14 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ps;
	size_t			i;

	ps = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		*(ps + i) = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	size_t	i;
	size_t	n;

	if (argc != 3)
		return (1);
	n = (size_t) atoi(argv[2]);
	if (n > strlen(argv[1]) + 1)
		return (1);
	printf("Avant : %s\n", argv[1]);
	ft_bzero(argv[1], n);
	i = 0;
	while (i < strlen(argv[1] + n) + n + 1)
	{
		printf("%d ", (unsigned char) argv[1][i]);
		i++;
	}
	printf("\n");
	return (0);
}
