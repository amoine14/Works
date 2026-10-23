/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 09:24:32 by username          #+#    #+#             */
/*   Updated: 2026/10/23 23:18:39 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
