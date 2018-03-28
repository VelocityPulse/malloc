/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:18:31 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/28 12:18:58 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/malloc.h"

int main()
{
	int        i;
	int			b;
	size_t    j;
	char    *s;

	i = 0;
	j = 1024;
	while (i < (int)j)
	{
		s = (char*)malloc(j);
		s[0] = 42;
//		free(s);
		i++;
	}
//	show_full_alloc_mem();
//	show_alloc_mem();
	return (0);
}
