/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:36:27 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/16 10:53:28 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		set_block(t_block *block, size_t size)
{
	block->size = size;
	block->next = NULL;
	block->status = USED;
	block->ptr = block + sizeof(t_block);
}

size_t		new_map(size_t map_type, t_map **map)
{
	size_t mmap_size;
	size_t size = 0;

	if (map_type == TINY_SIZE)
		mmap_size = MAP_ALIGN(TINY_MMAP_SIZE);
	else if (map_type == SMALL_SIZE)
		mmap_size = MAP_ALIGN(SMALL_MMAP_SIZE);
	*map = (t_map *) mmap(NULL, mmap_size, PROT, MAP, -1, 0);
	if (*map == MAP_FAILED)
		return (-1);
	//TODO : make a bzero on the mmap
	(*map)->size = mmap_size;
	(*map)->remaining = mmap_size - sizeof(t_map);
	(*map)->next = NULL;
	return (0);
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
		if (map->remaining > necessary_space)
		{
			block = (void *)map + sizeof(t_map);
			while (block->next != NULL) {
				if (block->status == FREE && block->size >= necessary_space) {
					block->status  = USED;
					return (block->ptr);
				}
				block = block->next;
			}
			set_block(block, size);
			//TODO sub the size to the remaining
			return (block->ptr);
		}
		else
		{
			last = map;
			map = map->next;
		}
	}
	new_map(map_type, &last->next); // TODO check if next is well overwrite
	return (get_free_space(map_type, last->next, size));
}


void		*malloc(size_t size)
{
	static t_map	*tiny_map = NULL;
	static t_map	*small_map = NULL;
	static t_map	*large_map = NULL;
	void			*ptr;

	size = ALIGN(size);
	ptr = NULL;
	if (size <= TINY_SIZE)
	{
		if (!tiny_map && new_map(TINY_SIZE, &tiny_map))
			return (NULL);
		ptr = get_free_space(TINY_SIZE, tiny_map, size);
	}
	/*
	   else if (size - sizeof(t_block) <= SMALL_SIZE)
	   {
	   if (!map.small && new_map(SMALL_SIZE, &map.small, &map.max_size))
	   return (NULL);
	   ptr = get_free_space(SMALL_SIZE, size, &map.tiny);

	   }

	   else
	   {
	// idk what im supposed to do rofl
	}
	*/
	return (ptr);
}
