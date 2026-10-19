/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_atoi.c                                         :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/19 15:41:41 by username         #+#    #+#              */
/*   Updated: 2026/10/19 15:54:11 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	neg;
	int	nb;
	int	i;

	neg = 1;
	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
			neg = -neg;
		else
		{
			nb = (10 * nb) + (str[i] - 48);
		}
		i++;
	}
	return (neg * nb);
}
