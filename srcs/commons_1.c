/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 13:58:38 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/27 10:36:29 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

char	digit(int nb)
{
	if (nb < 10)
		return ('0' + nb);
	return ('A' + nb % 10);
}

void	ft_puthexa(unsigned int n)
{
	char	c;

	if (n > 9)
		ft_puthexa(n / 16);
	n = n % 16;
	if (n < 10)
		c = '0' + n;
	else
		c = 'A' + n % 10;
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long nbr;

	nbr = n;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else
		ft_putchar(nbr + 48);
}
