/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:18:31 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/14 14:49:51 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/header.h"
#include <stdio.h>

int main()
{

	int *lol = malloc(2);

	printf("%d\n", getpagesize());
	int base_size = 5000;
	printf("%d - %d - %d", base_size + getpagesize(), base_size % getpagesize(), base_size + getpagesize() - (base_size % getpagesize()));
	return 1;
	DEBUG
	int i = 0;
	while (i <= 2495)
	{
//		lol[i] = 'a';
//		ft_printf("[%d] \n", i);
//		ft_printf("[%d] \n", lol[i]);
//		printf("%X = lol[i] = %d\n", lol[i], lol[i]);
		i++;
	}
	ft_printf("\n%d\n", sizeof(t_block));
	ft_printf("i + t_bloc = %d\n", i + sizeof(t_block));
	ft_printf("%d\n", getpagesize());

}
