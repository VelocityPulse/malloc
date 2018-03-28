/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:53:25 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/28 16:27:40 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		print_full_block(t_block *block, int *total)
{
	int		total_block;

	total_block = 0;
	while (block)
	{
		ft_putstr("Block : 0x");
		ft_puthexa((unsigned int)block);
		ft_putstr(" users : 0x");
		ft_puthexa((unsigned int)block->ptr);
		ft_putstr(" end : 0x");
		ft_puthexa((unsigned int)block->ptr + block->size);
		ft_putstr(" status : [");
		ft_putnbr(block->status);
		ft_putstr("] octect(s) : ");
		ft_putnbr(block->size);
		ft_putstr("\n");
		*total += block->size;
		block = block->next;
		total_block++;
	}
	ft_putstr("Number of block(s) : ");
	ft_putnbr(total_block);
	ft_putstr("\n");
}

static void		print_map_tiny(t_map *map, int *total)
{
	t_block		*block;

	while (map)
	{
		ft_putstr("TINY : 0x");
		ft_puthexa((unsigned int)map);
		ft_putstr("\n");
		block = (void *)map + sizeof(t_map);
		print_full_block(block, total);
		map = map->next;
	}
}

static void		print_map_small(t_map *map, int *total)
{
	t_block		*block;

	while (map)
	{
		ft_putstr("SMALL : 0x");
		ft_puthexa((unsigned int)map);
		ft_putstr("\n");
		block = (void *)map + sizeof(t_map);
		print_full_block(block, total);
		map = map->next;
	}
}

static void		print_map_large(t_map *map, int *total)
{
	t_block		*block;

	while (map)
	{
		ft_putstr("LARGE : 0x");
		ft_puthexa((unsigned int)map);
		ft_putstr("\n");
		block = (void *)map + sizeof(t_map);
		print_full_block(block, total);
		map = map->next;
	}
}

void			show_full_alloc_mem(void)
{
	int		total;

	total = 0;
	print_map_tiny(g_global.tiny_map, &total);
	print_map_small(g_global.small_map, &total);
	print_map_large(g_global.large_map, &total);
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octect(s)\n");
}
