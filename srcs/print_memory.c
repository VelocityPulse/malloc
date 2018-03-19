/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:53:25 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/19 12:17:44 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	print_block(t_block *block, int *total)
{
			while (block)
		{
			printf("0x%X - 0x%X : %zd octect(s)\n",
					(void *)block->ptr,
					(void *)block + block->size + sizeof(t_block),
					block->size);
			*total += block->size;
			block = block->next;
		}

}

void	print_map_tiny(t_map *map, int *total)
{
	t_block *block;
	while (map)
	{
		printf("TINY : 0x%X\n", (unsigned int)map);
		block = (void *)map + sizeof(t_map);
		print_block(block, total);
		map = map->next;
	}
}

void	print_map_small(t_map *map, int *total)
{
	t_block *block;
	while (map)
	{
		printf("SMALL : 0x%X\n", (unsigned int)map);
		block = (void *)map + sizeof(t_map);
		print_block(block, total);
		map = map->next;
	}

}

void	print_map_large(t_map *map, int *total) {
	t_block *block;
	while (map)
	{
		printf("LARGE : 0x%X\n", (unsigned int)map);
		block = (void *)map + sizeof(t_map);
		print_block(block, total);
		map = map->next;
	}
}

void	show_alloc_mem()
{
	int		total;

	total = 0;
	print_map_tiny(global.tiny_map, &total);
	print_map_small(global.small_map, &total);
	print_map_large(global.large_map, &total);
	printf("Total : %d octect(s)\n", total);
}
