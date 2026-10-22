/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 15:51:19 by username          #+#    #+#             */
/*   Updated: 2026/10/22 16:53:11 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_dec(int n)
{
	int	count;

	count = 1;
	while (n / 10 != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*convert(int n, int count)
{
	char	*str;
	int		end;

	end = count;
	str = malloc(sizeof(int) * (count) + 1);
	if (str == NULL)
		return (NULL);
	count--;
	while (count >= 0)
	{
		str[count] = (n % 10) + 48;
		printf("Cara = %c\n", str[count]);
		n /= 10;
		count--;
	}
	str[end] = '\0';
	return (str);
}

static char	*convertn(int n, int count)
{
	char	*str;
	int		end;

	end = count + 1;
	n *= -1;
	str = malloc(sizeof(int) * (count) + 2);
	if (str == NULL)
		return (NULL);
	while (count > 0)
	{
		str[count] = (n % 10) + 48;
		printf("Cara = %c\n", str[count]);
		n /= 10;
		count--;
	}
	str[0] = '-';
	str[end] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;

	count = count_dec(n);
	if (n < 0)
		str = convertn(n, count);
	else
		str = convert(n, count);
	printf("Final = %s\n", str);
	return (str);
}

int	main(int argc, char **argv)
{
	argc = argc;
	ft_itoa(ft_atoi(argv[1]));
	return (0);
}
