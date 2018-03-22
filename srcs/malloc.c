/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:36:27 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/22 12:52:24 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_global		g_global = {NULL, NULL, NULL};

t_block		*set_block(t_block *block, size_t size)
{
	block->size = size;
	block->next = NULL;
	block->status = USED;
	block->ptr = (void *)block + sizeof(t_block);
	return (block);
}

size_t		new_map(size_t map_type, t_map **map)
{
	size_t mmap_size;
	size_t size = 0;

	if (map_type == TINY_SIZE)
		mmap_size = MAP_ALIGN(TINY_MMAP_SIZE);
	else if (map_type == SMALL_SIZE)
		mmap_size = MAP_ALIGN(SMALL_MMAP_SIZE);
	else
		mmap_size = map_type + sizeof(t_map) + sizeof(t_block);
	*map = (t_map *) mmap(NULL, mmap_size, PROT, MAP, -1, 0);
	if (*map == MAP_FAILED)
		return (_ERROR_);
	(*map)->size = mmap_size;
	(*map)->remaining = mmap_size - sizeof(t_map);
	(*map)->next = NULL;
	return (_SUCCESS_);
}

int			check_block_pointer(t_block *block, t_map *map)
{
	if ((void *)block > (void *)map &&
			(unsigned int)block < (unsigned int)map + map->size)
		return (_SUCCESS_);
	return (_ERROR_);
}

void	optimize_and_split_blocks(t_block *block)
{
	t_block		*new_block;
	int			free_size;
	int			total_space;

	total_space = (void *)block->next - (void *)block->ptr;
	if (total_space - block->size >= sizeof(t_block) + 4)
	{
		new_block = (t_block *)((void *)block->ptr + block->size);
		free_size = total_space - sizeof(t_block) - block->size - 1;
		free_size = ALIGN(free_size);
		if ((void *)new_block + sizeof(t_block) + free_size > (void *)block->next)
			free_size -= 4;
		set_block(new_block, free_size);
		new_block->next = block->next;
		block->next = new_block;
		new_block->status = FREE;
	}
}

void		*get_free_space(size_t map_type, t_map *map, size_t size)
{
	t_map *last;
	t_block *block;
	size_t necessary_space;

	necessary_space = size + sizeof(t_block);
	last = map;
	while (map)
	{
		// TODO make more check
		if (map->remaining > necessary_space) // EACH MAP
		{
			block = (void *)map + sizeof(t_map);
			if (block->status == FREE && block->size == 0) // for the first
			{
				set_block(block, size);
				map->remaining -= necessary_space;
				return block->ptr;
			}
			while (block) { // EACH BLOCK
				if (block->status == FREE && block->size >= size) {
					map->remaining -= necessary_space;
					block->size = size;
					block->status = USED;
					if (block->next)
						optimize_and_split_blocks(block);
					return block->ptr;
				}
				if (block->next &&
						check_block_pointer(block->next, map) == _ERROR_)
					return NULL;
				if (block->next == NULL)
				{
					// FINALLY
					block->next = (void *)block + sizeof(t_block) + block->size;
					block = block->next;
					set_block(block, size);
					map->remaining -= necessary_space;
					return block->ptr;
				}
				block = block->next;
			}
		}
		else
		{
			last = map;
			map = map->next;
		}
	}
	new_map(map_type, &last->next);
	return (get_free_space(map_type, last->next, size));
}

void		*malloc(size_t size)
{
	void			*ptr;

	size = ALIGN(size);
	ptr = NULL;
	if (size <= TINY_SIZE)
	{
		if (!g_global.tiny_map && !new_map(TINY_SIZE, &g_global.tiny_map))
			return (NULL);
		ptr = get_free_space(TINY_SIZE, g_global.tiny_map, size);
	}

	else if (size <= SMALL_SIZE)
	{
		if (!g_global.small_map && !new_map(SMALL_SIZE, &g_global.small_map))
			return (NULL);
		ptr = get_free_space(SMALL_SIZE, g_global.small_map, size);
	}
	else
	{
		if (!g_global.large_map && !new_map(size, &g_global.large_map))
			return (NULL);
		ptr = get_free_space(size, g_global.large_map, size);
	}
	return (ptr);
}
