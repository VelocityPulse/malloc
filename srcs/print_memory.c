/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:53:25 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/16 16:53:48 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	show_alloc_mem()
{
	// debug
	printf("TINY : 0x%X\n", (unsigned int)global.tiny_map);
	
	t_map	*tiny_map = global.tiny_map;
	t_block *block;
	while (tiny_map)
	{
		block = (void *)tiny_map + sizeof(t_map);
		while (block)
		{
			printf("0x%X - 0x%X : %zd octect(s)\n",
					(void *)block->ptr,
					(void *)block + block->size + sizeof(t_block),
					block->size);
			block = block->next;
		}
		tiny_map = tiny_map->next;
	}

}
