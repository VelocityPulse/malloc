/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:18:31 by cchameyr          #+#    #+#             */
/*   Updated: 2017/08/07 13:18:23 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/header.h"
#include <stdio.h>

int main()
{
	void *ptr;
	int i = 10;

	ptr = (char *)mmap(NULL, 2 * getpagesize(), PROT, MAP, -1, 0);



	ptr = malloc(i);
	printf("size : %u\n", sizeof(t_map));
	int size = 5000;
	printf("size 2 : %d\n", size);

	printf("1 : %d\n2 : %d\n3 : %d\n4 : %d\n5 : %d\n",
			size,
			getpagesize(),
			size % getpagesize(),
			getpagesize() - (size % getpagesize()),
			size + (getpagesize() - (size % getpagesize())));

	printf("getpagesize * 2 : %d\n", getpagesize() * 2);

	return (0);
	ft_printf("-----malloc function success-----\n");
	ft_printf("[%d]\n", ptr);
	ft_bzero(ptr, i);
	while (--i)
		ft_printf("[%d]\n", ptr + i);
}
