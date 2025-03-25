/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:50:45 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/27 15:18:44 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_flags(const char *str_char, va_list args, unsigned int *counter)
{
	void	*ptr;

	if (*str_char == 'c')
		*counter += write(1, &(char){va_arg(args, int)}, 1);
	else if (*str_char == 'u')
		ft_putunbr(va_arg(args, unsigned int), counter);
	else if (*str_char == 'd' || *str_char == 'i')
		ft_putnbr(va_arg(args, int), counter);
	else if (*str_char == 's')
		ft_putstr(va_arg(args, const char *), counter);
	else if (*str_char == 'x' || *str_char == 'X')
		ft_puthex(va_arg(args, unsigned int), *str_char, counter);
	else if (*str_char == 'p')
	{
		ptr = va_arg(args, void *);
		if (ptr == NULL)
			ft_putstr("(nil)", counter);
		else
		{
			ft_putstr("0x", counter);
			ft_puthexp((unsigned long)ptr, counter);
		}
	}
}

int	ft_printf(const char *str, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	result;

	if (!str)
		return (-1);
	i = 0;
	result = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
				result += write(1, "%", 1);
			else
				ft_flags(&str[i + 1], args, &result);
			i++;
		}
		else
			result += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (result);
}

/*#include <stdio.h>

int	main()
{
	ft_printf("Hello, world!\n");
	printf("Hello, world!\n");
	ft_printf("The number is %d\n", 42);
	printf("The number is %d\n", 42);
	ft_printf("the character is %c\n", 'A');
	printf("The character is %c\n", 'A');
	ft_printf("The string is %s\n", "example");
	printf("The string is %s\n", "example");
	ft_printf("The hexadecimal is %x\n", 255);
	printf("The hexadecimal is %x\n", 255);
	ft_printf("test %p %c\n", NULL, 'A');
	printf("test %p %c\n", NULL, 'A');

	return 0;
}*/
