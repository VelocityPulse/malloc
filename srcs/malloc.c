/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:36:27 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/27 10:29:12 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_global		g_global = {NULL, NULL, NULL};



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
