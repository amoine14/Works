/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 08:57:45 by username          #+#    #+#             */
/*   Updated: 2026/10/23 08:58:07 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	to_upper(unsigned int i, char *c)
{
	(void) i;
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

void	upper_even(unsigned int i, char *c)
{
	if (i % 2 == 0 && *c >= 'a' && *c <= 'z')
		*c -= 32;
}

void	replace_digits(unsigned int i, char *c)
{
	(void) i;
	if (*c >= '0' && *c <= '9')
		*c = 'X';
}

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f((unsigned int) i, &s[i]);
		i++;
	}
}

// int	main(void)
// {
// 	char	s1[] = "bonjour";
// 	char	s2[] = "bonjour";
// 	char	s3[] = "abc123def456";
// 	char	s4[] = "";

// 	ft_striteri(s1, to_upper);
// 	ft_striteri(s2, upper_even);
// 	ft_striteri(s3, replace_digits);
// 	ft_striteri(s4, to_upper);
// 	printf("Test 1 : [%s]\n", s1);
// 	printf("Test 2 : [%s]\n", s2);
// 	printf("Test 3 : [%s]\n", s3);
// 	printf("Test 4 : [%s]\n", s4);
// 	return (0);
// }
