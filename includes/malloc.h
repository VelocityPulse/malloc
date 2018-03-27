/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 12:11:40 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/27 10:34:51 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>
//# include <stdlib.h>
//# include "../libft/libft.h"

# ifndef RETURN_STAT
#  define RETURN_STAT

#  define _FAULT_		0x00
#  define _ERROR_		0x00
#  define _SUCCESS_		0x01

# endif


# define PAGE_SIZE (size_t)getpagesize()

# define ALIGN(SIZE) (((SIZE - 1) + 4) - ((SIZE - 1) % 4))
# define MAP_ALIGN(SIZE) (((SIZE - 1) + PAGE_SIZE) - ((SIZE - 1) % PAGE_SIZE))

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
//#include "../../Perso/debug.h"

extern struct s_global	g_global;

/*
** map size : 24
*/

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

/*
** block size : 32
*/

typedef struct		s_block
{
	size_t			size;
	struct s_block	*next;
	char			status;
	void			*ptr;
}					t_block;

void				show_alloc_mem();
void				show_full_alloc_mem();

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);

void				*get_free_space(size_t map_type, t_map *map, size_t size);
size_t				new_map(size_t map_type, t_map **map);

t_block				*set_block(t_block *block, size_t size);
int					check_block_in_map(t_block *block, t_map *map);
int					check_pointer_validity(void *ptr, t_map *map);

void				ft_putstr(char *str);
void				ft_putnbr(int n);
void		ft_puthexa(unsigned int n);

#endif
