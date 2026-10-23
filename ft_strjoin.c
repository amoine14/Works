/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 10:51:23 by username          #+#    #+#             */
/*   Updated: 2026/10/23 23:13:50 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*concat(const char *s1, const char *s2, size_t lenp, size_t lens)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * (lens + lenp) + 1);
	if (str == NULL)
		return (NULL);
	while (i < lenp)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < lens)
	{
		str[i + lenp] = s2[i];
		i++;
	}
	str[i + lenp] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lenp;
	size_t	lens;

	lenp = 0;
	lens = 0;
	lenp = ft_strlen(s1);
	lens = ft_strlen(s2);
	return (concat(s1, s2, lenp, lens));
}
