/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:49:57 by username          #+#    #+#             */
/*   Updated: 2026/10/23 23:16:51 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ps;
	size_t				i;

	i = 0;
	ps = (const unsigned char *) s;
	while (i < n && ps[i] != (unsigned char) c)
		i++;
	if (i < n)
		return ((void *)(ps + i));
	return (NULL);
}
