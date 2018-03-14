/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:36:27 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/14 17:33:43 by cchameyr         ###   ########.fr       */
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

void		*get_free_space(size_t base_size, size_t size, void **map)
{
	t_block		*block;

	block = (t_block *)*map;
	DEBUG
		while (block)
		{
			DEBUG
				if (block->size >= base_size && block->status == FREE)
				{
					DEBUG
						//			set_block(block, size);
						block->status = USED;
					block->size = size;
					block->next = block + size;
					return (block->ptr);
				}
			block = block->next;
		}
	DEBUG
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
	(*map)->size = mmap_size;
	(*map)->remaining = mmap_size - sizeof(t_map);
	(*map)->next = NULL;
	//set_block((*map)->map, size); // WORK THIS PART IN FUTURE
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
		return (0);
//		ptr = get_free_space(TINY_SIZE, size, (void **) &tiny_map);
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
