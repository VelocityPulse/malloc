/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:36:27 by cchameyr          #+#    #+#             */
/*   Updated: 2017/08/08 11:48:13 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int init_map(t_map *map)
{
	struct rlimit	limit;

	if (map->max_size != 0)
		return (_SUCCESS_);
	if (getrlimit(RLIMIT_DATA, &limit) == -1)
		return (_ERROR_);
	map->max_size = limit.rlim_cur;
	return (_SUCCESS_);
}

void	*get_free_space(int base_size, int size, void *map)
{
	
	return (NULL);
}

int		new_map(int base_size, void **map)
{
	


	return (0);
}



void	*malloc(size_t size)
{
	static t_map	map = {0, 0, NULL, NULL, 0};
	void			*ptr;

	//return (NULL);
	if (size > map.max_size || size + sizeof(t_block) > map.max_size)
		return (NULL);
	size += sizeof(t_block);
	if (size - sizeof(t_block) <= TINY_SIZE)
	{
		if (!map.tiny && new_map(TINY_SIZE, &map.tiny))
			return (NULL);
		ptr = get_free_space(TINY_SIZE, size, &map.tiny);
	}

	else if (size - sizeof(t_block) <= SMALL_SIZE)
	{
		if (!map.small && new_map(SMALL_SIZE, &map.small))
			return (NULL);
		ptr = get_free_space(SMALL_SIZE, size, &map.tiny);

	}

	else
	{
	// idk what im supposed to do rofl
	}

	return (ptr);
}
