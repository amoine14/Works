/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:55:22 by username          #+#    #+#             */
/*   Updated: 2026/10/21 15:14:07 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static size_t	count_words(const char *str, char cara)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == cara)
			str++;
		if (*str)
			count++;
		while (*str && *str != cara)
			str++;
	}
	return (count);
}

static char	**free_split(char **tab, size_t count)
{
	while (count > 0)
	{
		count--;
		free(tab[count]);
	}
	free(tab);
	return (NULL);
}

static char	**fill_words(char **tab, const char *str, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (!*str)
			break ;
		len = 0;
		while (str[len] && str[len] != c)
			len++;
		tab[i] = ft_substr(str, 0, len);
		if (!tab[i])
			return (free_split(tab, i));
		i++;
		str += len;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	return (fill_words(tab, s, c));
}

// int	main(int argc, char **argv)
// {
// 	char	**tab;
// 	size_t	i;

// 	argc = argc;
// 	tab = ft_split(argv[1], ':');
// 	if (!tab)
// 	{
// 		printf("Erreur d'allocation\n");
// 		return (1);
// 	}
// 	i = 0;
// 	while (tab[i])
// 	{
// 		printf("tab[%zu] = \"%s\"\n", i, tab[i]);
// 		free(tab[i]);
// 		i++;
// 	}
// 	printf("tab[%zu] = NULL\n", i);
// 	free(tab);
// 	return (0);
// }
