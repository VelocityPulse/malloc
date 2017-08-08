/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:36:27 by cchameyr          #+#    #+#             */
/*   Updated: 2017/08/08 16:13:02 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	init_map(t_map *map)
{
	struct rlimit	limit;

	if (map->max_size != 0)
		return (_SUCCESS_);
	if (getrlimit(RLIMIT_DATA, &limit) == -1)
		return (_ERROR_);
	map->max_size = limit.rlim_cur;
	return (_SUCCESS_);
}

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

size_t		new_map(size_t base_size, void **map, size_t *max_size)
{
	size_t size;

	size = base_size + getpagesize() - (base_size % getpagesize());
	if (size > *max_size)
		return (-1);
//	ft_printf("size1 : %d\n", (int)size);
	*map = mmap(NULL, size, PROT, MAP, -1, 0);
	if (*map == MAP_FAILED)
		return (-1);
	*max_size = *max_size - size;
	set_block(*map, size);
	return (0);
}

void		*malloc(size_t size)
{
	static t_map	map = {NULL, NULL, 0};
	void			*ptr;

	//return (NULL);
	ptr = NULL;
	init_map(&map);
	if (size > map.max_size || size + sizeof(t_block) > map.max_size)
		return (NULL);
	size += sizeof(t_block);
	if (size - sizeof(t_block) <= TINY_SIZE)
	{
		if (!map.tiny && new_map(TINY_SIZE, &map.tiny, &map.max_size))
			return (NULL);
		ptr = get_free_space(TINY_SIZE, size, &map.tiny);
		DEBUG
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
