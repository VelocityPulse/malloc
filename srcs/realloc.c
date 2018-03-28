/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 10:38:20 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/28 12:18:32 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		*make_new_ptr(t_block *block, void *ptr, size_t size)
{
	void *new_ptr;

	if (!(new_ptr = malloc(size)))
		return NULL;
	new_ptr = ft_memmove(new_ptr, ptr, block->size);
	free(ptr);
	return new_ptr;
}

static void		*realloc_process(void *ptr, t_map *map, size_t size)
{
	t_map	*last;
	t_block *block;

	last = NULL;
	while (map)
	{
		if (check_pointer_validity(ptr, map) == _SUCCESS_)
		{
			block = (t_block *)ptr - sizeof(t_block);
			if (block->next && block->next->status == FREE &&
					block->next->size + sizeof(t_block) > size)
			{
				block->next = block->next->next;
				block->size = block->size + block->next->size + sizeof(t_block);
				return ptr;
			}
			else
				make_new_ptr(ptr, block, size);
		}
		last = map;
		map = map->next;
	}
	return (_ERROR_);
}

void	*realloc(void *ptr, size_t size)
{
	t_map *map;
	void	*ret;

	if (ptr == NULL)
		return (malloc(size));
	if (ptr == NULL || size == 0)
		return NULL;
	map = g_global.tiny_map;
	if ((ret = realloc_process(ptr, g_global.tiny_map, size)) != _ERROR_)
		return ret;
	if ((ret = realloc_process(ptr, g_global.small_map, size)) != _ERROR_)
		return ret;
	if ((ret = realloc_process(ptr, g_global.large_map, size)) != _ERROR_)
		return ret;
	if (!size)
	{
		free(ptr);
		return (malloc(size));
	}
	return NULL;
}
