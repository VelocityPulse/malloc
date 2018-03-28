/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 10:28:44 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/28 10:28:47 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"



t_block		*set_block(t_block *block, size_t size)
{
	block->size = size;
	block->next = NULL;
	block->status = USED;
	block->ptr = (void *)block + sizeof(t_block);
	return (block);
}

int			check_block_in_map(t_block *block, t_map *map)
{
	if ((void *)block > (void *)map &&
			(unsigned int)block < (unsigned int)map + map->size)
		return (_SUCCESS_);
	return (_ERROR_);
}

int		check_pointer_validity(void *ptr, t_map *map)
{
	t_block		*block;

	if (ptr > (void *)map && (unsigned int)ptr < (unsigned int)map + map->size)
	{
		block = (void *)map + sizeof(t_map);
		while (block)
		{
			if (block->ptr == ptr)
				return (_SUCCESS_);
			block = block->next;
		}
	}
	return (_ERROR_);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;

	s = (char *)src;
	d = (char *)dst;
	if (n == 0 || d == s)
		return ((void *)d);
	while (--n)
		*d++ = *s++;
	*d = *s;
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	if (dst == src && !len)
		return (NULL);
	d = (char *)dst;
	s = (char *)src;
	if (d > s)
	{
		while (len--)
			d[len] = s[len];
	}
	else
		dst = ft_memcpy(dst, (void *)src, len);
	return (dst);
}
