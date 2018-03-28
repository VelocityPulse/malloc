/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:53:25 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/28 16:29:22 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		print_block(t_block *block, int *total)
{
	while (block)
	{
		if (block->status == USED)
		{
			ft_putstr("0x");
			ft_puthexa((unsigned int)block->ptr);
			ft_putstr(" - 0x");
			ft_puthexa((unsigned int)block->ptr + block->size);
			ft_putstr(" : ");
			ft_putnbr(block->size);
			ft_putstr(" octect(s)\n");
			*total += block->size;
		}
		block = block->next;
	}
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
		print_block(block, total);
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
		print_block(block, total);
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
		print_block(block, total);
		map = map->next;
	}
}

void			show_alloc_mem(void)
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
