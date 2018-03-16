/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:36:27 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/16 16:50:57 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_global		global = {NULL, NULL, NULL};

void		set_block(t_block *block, size_t size)
{
	block->size = size;
	block->next = NULL;
	block->status = USED;
	block->ptr = (void *)block + sizeof(t_block);
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
	ft_bzero((void *)*map, mmap_size); // TODO check if it work
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
//			printf("[%d] [%d] [%d] [%d]\n", block->size, block->next, block->status, block->ptr);
			if (block->status == FREE && block->size == 0)
			{
				DEBUG
				set_block(block, size);
				return block->ptr;
			}
			while (block->next) { // check if its not FREE
				block = block->next;
				DEBUG
			}
			DEBUG
			block->next = (void *)block + sizeof(t_block) + block->size;
			block = block->next;
			set_block(block, size);
			return block->ptr;


//////////////////////////////////////////////////
	//		DEBUG
			block = (void *)map + sizeof(t_map);
			while (block->next != NULL) {
				if (block->status == FREE && block->size >= necessary_space) {
					block->status  = USED;
					return (block->ptr);
				}
				block = block->next;
			}
			set_block(block, size);
			block->next = block + sizeof(t_block) + block->size;
			map->remaining -= necessary_space;
			return (block->ptr);
		}
		else
		{
	//		DEBUG
			last = map;
			map = map->next;
		}
	}
	new_map(map_type, &last->next); // TODO check if next is well overwrite
	return (get_free_space(map_type, last->next, size));
}


void		*malloc(size_t size)
{
	void			*ptr;

	size = ALIGN(size);
	ptr = NULL;
	if (size <= TINY_SIZE)
	{
		if (!global.tiny_map && new_map(TINY_SIZE, &global.tiny_map))
			return (NULL);
		ptr = get_free_space(TINY_SIZE, global.tiny_map, size);
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
