/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 10:12:04 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/27 10:35:14 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/malloc.h"

size_t		new_map(size_t map_type, t_map **map)
{
	size_t mmap_size;

	if (map_type == TINY_SIZE)
		mmap_size = MAP_ALIGN(TINY_MMAP_SIZE);
	else if (map_type == SMALL_SIZE)
		mmap_size = MAP_ALIGN(SMALL_MMAP_SIZE);
	else
		mmap_size = map_type + sizeof(t_map) + sizeof(t_block);
	*map = mmap(NULL, mmap_size, PROT, MAP, -1, 0);
	if (*map == MAP_FAILED)
		return (_ERROR_);
	(*map)->size = mmap_size;
	(*map)->remaining = mmap_size - sizeof(t_map);
	(*map)->next = NULL;
	return (_SUCCESS_);
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

void		*find_block(t_block *block, t_map *map, size_t n_s, int size)
{
	while (block) {
		if (block->status == FREE && block->size >= size) {
			block->size = size;
			block->status = USED;
			map->remaining -= n_s;
			if (block->next)
				optimize_and_split_blocks(block);
			return block->ptr;
		}
		if (block->next &&
				check_block_in_map(block->next, map) == _ERROR_)
			return (void *)-1;
		if (block->next == NULL)
		{
			map->remaining -= n_s;
			block->next = block->ptr + block->size;
			block = block->next;
			set_block(block, size);
			return block->ptr;
		}
		block = block->next;
	}
	return NULL;
}

void		*check_map(t_map *map, size_t n_s, int size)
{
	void	*ret;
	t_block	*block;

	if (map->remaining > n_s)
	{
		block = (void *)map + sizeof(t_map);
		if (block->status == FREE && block->size == 0)
		{
			set_block(block, size);
			map->remaining -= n_s;
			return block->ptr;
		}
		ret = find_block(block, map, n_s, size);
		if ((int)ret == -1)
			return (void *)-1;
		else if (ret != NULL)
			return ret;
	}
	return NULL;
}

void		*get_free_space(size_t map_type, t_map *map, size_t size)
{
	t_map *last;
	t_block *block;
	void	*ret;
	size_t necessary_space;

	necessary_space = size + sizeof(t_block);
	last = map;
	while (map)
	{
		ret = check_map(map, necessary_space, size);
		if (ret == NULL)
		{
			last = map;
			map = map->next;
		}
		else if ((int)ret == -1)
			return NULL;
		else if (ret != NULL)
			return ret;
	}
	new_map(map_type, &last->next);
	return (get_free_space(map_type, last->next, size));
}
