/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 12:08:25 by username          #+#    #+#             */
/*   Updated: 2026/10/20 12:15:24 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < n)
		i++;
	return (s1[i] - s2[i]);
}

// int	main(void)
// {
// 	char	*s1 = "Bonjour";
// 	char	*s2 = "BonjwqouR";
// 	size_t	n = 7;
// 	int		ret_ft;
// 	int		ret_original;

// 	ret_ft = ft_strncmp(s1, s2, n);
// 	ret_original = strncmp(s1, s2, n);
// 	printf("s1 : %s\n", s1);
// 	printf("s2 : %s\n", s2);
// 	printf("n  : %zu\n", n);
// 	printf("ft_strncmp : %d\n", ret_ft);
// 	printf("strncmp    : %d\n", ret_original);
// 	return (0);
// }
