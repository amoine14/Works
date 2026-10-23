/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 16:55:03 by username          #+#    #+#             */
/*   Updated: 2026/10/23 23:19:43 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *) big);
	while (i < len && big[i])
	{
		j = 0;
		while (j < len - i && big[i + j] == little[j])
		{
			j++;
			if (!(little[j]))
				return ((char *)(big + i));
		}
		i++;
	}
	return ((NULL));
}
