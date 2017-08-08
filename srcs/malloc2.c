/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:03:57 by cchameyr          #+#    #+#             */
/*   Updated: 2017/08/04 10:34:33 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

#include <fcntl.h>

void	*malloc(size_t size) 
{
	char *test_alloc1;
	int fd = open("/dev/zero", O_RDWR, 0);

	(void)size;
	ft_printf("get page size      : %d\n", getpagesize());
	ft_printf("fd value           : %d\n", fd);
	if (fd == -1)
		return (NULL);
	test_alloc1 = (char *)mmap(NULL, 3, PROT_WRITE|PROT_READ, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	close(fd);

	ft_printf("adress test_alloc1 : %d\n", test_alloc1);
	ft_printf("writing in test_alloc1...\n");
	ft_bzero(test_alloc1, 4097);
	test_alloc1[0] = 'q';
	test_alloc1[1] = 'w';
	test_alloc1[2] = 'e';
	ft_printf("result test_alloc1 : %s\n", test_alloc1);


	ft_printf("TINY SIZE          : %d\n", TINY);
	ft_printf("SMALL SIZE         : %d\n", SMALL);
	ft_printf("LARGE SIZE         : %d\n", LARGE);

	return (NULL);
}
