/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2018/03/28 14:26:19 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	ft_putstr_test(char const *str)
{
	while (*str)
		write(1, str++, 1);
}

int		main(void)
{
	malloc(1024);
	malloc(1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	ft_putstr_test("\n---------show_alloc_mem()------------\n");
	show_alloc_mem();
//	ft_putstr("\n---------show_alloc_mem_ex()---------\n");
//	show_alloc_mem_ex();
	return (0);
}
