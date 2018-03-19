/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:18:31 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/19 10:51:21 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/header.h"
#include <stdio.h>

int main()
{
	int *x;
	int index = -1;
/*	int *lol = malloc(30);
	DEBUG
	lol = malloc(30);
	DEBUG
	lol = malloc(2);
	lol = malloc(65);
	lol = malloc(200);
	DEBUG
	show_alloc_mem();
*/
	
	while (++index < 400) {
		x = malloc(1000);
		//DEBUG
	}
	index = -1;
	while (++index < 2000) {
	x = malloc(20);
	}
//	x = malloc(1000);
//	x = malloc(1000);

	//show_alloc_mem();
	return 1;
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
