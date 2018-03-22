/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 12:11:40 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/22 13:14:30 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define PAGE_SIZE (size_t)getpagesize() * 16

# define ALIGN(SIZE) (((SIZE - 1) + 4) - ((SIZE - 1) % 4))
# define MAP_ALIGN(SIZE) ((SIZE + PAGE_SIZE) - (SIZE % PAGE_SIZE))

# define MAP_HEADER sizeof(t_map)
# define BLOCK_HEADER sizeof(t_block)

# define TINY_SIZE 1024
# define SMALL_SIZE (TINY_SIZE * 30)

# define TINY_MMAP_SIZE (MAP_HEADER + ((BLOCK_HEADER + TINY_SIZE) * 100))
# define SMALL_MMAP_SIZE (MAP_HEADER + ((BLOCK_HEADER + SMALL_SIZE) * 100))

# define USED 1
# define FREE 0

# define PROT PROT_WRITE|PROT_READ
# define MAP MAP_ANONYMOUS|MAP_PRIVATE

//debug
#include "../../Perso/debug.h"

extern struct s_global		g_global;

typedef struct		s_map
{
	size_t			size;
	size_t			remaining;
	struct s_map	*next;
}					t_map;

typedef struct		s_global
{
	t_map			*tiny_map;
	t_map			*small_map;
	t_map			*large_map;
}					t_global;

typedef struct		s_block
{
	size_t			size;
	struct s_block	*next;
	char			status;
	void			*ptr;
}					t_block;

void	show_alloc_mem();

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);



#endif
