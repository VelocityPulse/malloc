/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:56:25 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/28 15:33:40 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		optimize_and_merge_blocks(t_map *map)
{
	t_block		*block;

	block = (void *)map + sizeof(t_map);
	while (block->next)
	{
		if (block->status == FREE && block->next->status == FREE)
		{
			block->size += block->next->size + sizeof(t_block);
			block->next = block->next->next;
			optimize_and_merge_blocks(map);
			return ;
		}
		block = block->next;
	}
}

static int		unmap_if_necessary(t_map *map, t_map *last)
{
	t_block		*block;

	if (!map->next)
		return (_ERROR_);
	block = (void *)map + sizeof(t_map);
	while (block)
	{
		if (block->status == USED)
			return (_ERROR_);
		block = block->next;
	}
	if (g_global.tiny_map == map)
		g_global.tiny_map = map->next;
	else if (g_global.small_map == map)
		g_global.small_map = map->next;
	else if (g_global.large_map == map)
		g_global.large_map = map->next;
	if (last != NULL)
		last->next = map->next;
	munmap(map, map->size);
	return (_SUCCESS_);
}

static int		browse_map_membership(void *ptr, t_map *map)
{
	t_map	*last;
	t_block *block;

	last = NULL;
	while (map)
	{
		if (check_pointer_validity(ptr, map) == _SUCCESS_)
		{
			ptr = ptr - sizeof(t_block);
			block = (t_block *)ptr;
			block->status = FREE;
			map->remaining += sizeof(t_block) + block->size;
			if (!unmap_if_necessary(map, last))
				optimize_and_merge_blocks(map);
			return (_SUCCESS_);
		}
		last = map;
		map = map->next;
	}
	return (_ERROR_);
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_locker);
	if (ptr == NULL)
		return ;
	if (browse_map_membership(ptr, g_global.tiny_map) == _SUCCESS_)
		return ;
	if (browse_map_membership(ptr, g_global.small_map) == _SUCCESS_)
		return ;
	if (browse_map_membership(ptr, g_global.large_map) == _SUCCESS_)
		return ;
	pthread_mutex_unlock(&g_locker);
}
