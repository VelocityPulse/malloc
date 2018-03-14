/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:36:27 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/14 18:05:20 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		set_block(t_block *block, size_t size)
{
	block->size = size;
	block->next = NULL;
	block->back = NULL;
	block->status = FREE;
	block->ptr = block + sizeof(t_block);
	DEBUG
	printf("ptr = %X\n", (unsigned int)&block->ptr);
}

void		*get_free_space(t_map *map, size_t size)
{
	t_map *cur;
	t_block *block;
	size_t necessary_space;

	necessary_space = size + sizeof(t_block);
	
	cur = map;
	while (map)
	{
		if (map->remaining > necessary_space) 
		{
			block = (void *)map + sizeof(t_map);
			while (block->next != NULL) {
				if (block->status == FREE && block->size >= necessary_space) {
					block->status  = USED;
					return block->ptr;
				}
				block = block->next;
				//TODO continu here
			}
		}

	}





	return NULL;
///////////////////////////////////////////////////////////
	t_block		*block;

	block = (t_block *)*map;
		while (block)
		{
				if (block->size >= base_size && block->status == FREE)
				{
//					set_block(block, size);
					block->status = USED;
					block->size = size;
					block->next = block + size;
					return (block->ptr);
				}
			block = block->next;
		}
		return (NULL);
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
		ptr = get_free_space(tiny_map, size);
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
