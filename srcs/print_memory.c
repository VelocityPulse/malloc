/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:53:25 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/22 12:22:11 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	print_full_blocks(t_block *block, int *total)
{
	int		total_block;

	total_block = 0;
	while (block)
	{
		printf("block : 0x%X users : 0x%X end : 0x%X status : %d octect(s) : %zu\
				\n",
				(unsigned int)block, (unsigned int)block->ptr,
				(unsigned int)block->ptr + block->size,
				block->status, block->size);
		*total += block->size;
		block = block->next;
		total_block++;
	}
	printf("total block : %d\n", total_block);
}

void	print_block(t_block *block, int *total)
{
	print_full_blocks(block, total);
	return ;
	while (block)
	{
		if (block->status == USED)
		{
			printf("0x%X - 0x%X : %zd octect(s)\n",
					(void *)block->ptr,
					(void *)block->ptr + block->size,
					block->size);
			*total += block->size;
		}
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
	print_map_tiny(g_global.tiny_map, &total);
	print_map_small(g_global.small_map, &total);
	print_map_large(g_global.large_map, &total);
	printf("Total : %d octect(s)\n", total);
}
