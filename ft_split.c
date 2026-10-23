/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:55:22 by username          #+#    #+#             */
/*   Updated: 2026/10/23 23:14:26 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*copy_word(const char *str, size_t len)
{
	char	*word;
	size_t	i;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
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
		tab[i] = copy_word(str, len);
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
