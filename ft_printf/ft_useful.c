/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_useful.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:52:27 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/27 15:19:02 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putstr(const char *s, unsigned int *counter)
{
	int	i;

	i = 0;
	if (!s)
	{
		*counter += write(1, "(null)", 6);
		return ;
	}
	while (s[i] != '\0')
	{
		*counter += write(1, &s[i], 1);
		i++;
	}
	return ;
}

void	ft_putnbr(int n, unsigned int *counter)
{
	char	res;

	if (n == -2147483648)
	{
		ft_putnbr(n / 10, counter);
		*counter += write(1, "8", 1);
	}
	else if (n < 0)
	{
		*counter += write(1, "-", 1);
		ft_putnbr(-n, counter);
	}
	else
	{
		if (n > 9)
			ft_putnbr(n / 10, counter);
		res = (n % 10) + '0';
		*counter += write(1, &res, 1);
	}
}

void	ft_putunbr(unsigned int n, unsigned int *counter)
{
	char	res;

	if (n > 9)
		ft_putunbr(n / 10, counter);
	res = (n % 10) + '0';
	*counter += write(1, &res, 1);
}

void	ft_puthex(unsigned int hex, char uppercase, unsigned int *counter)
{
	char	*alpha;

	if (uppercase == 'X')
		alpha = "ABCDEF";
	else
		alpha = "abcdef";
	if ((hex / 16) == 0)
	{
		if ((hex % 16) < 10)
			ft_putnbr(hex % 16, counter);
		else
			*counter += write(1, &alpha[hex % 16 - 10], 1);
		return ;
	}
	ft_puthex(hex / 16, uppercase, counter);
	if (hex % 16 < 10)
		ft_putnbr(hex % 16, counter);
	else
		*counter += write(1, &alpha[hex % 16 - 10], 1);
}

void	ft_puthexp(unsigned long hex, unsigned int *counter)
{
	char	*alpha;

	alpha = "abcdef";
	if ((hex / 16) == 0)
	{
		if ((hex % 16) < 10)
			ft_putnbr(hex % 16, counter);
		else
			*counter += write(1, &alpha[hex % 16 - 10], 1);
		return ;
	}
	ft_puthexp(hex / 16, counter);
	if (hex % 16 < 10)
		ft_putnbr(hex % 16, counter);
	else
		*counter += write(1, &alpha[hex % 16 - 10], 1);
}
