/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 12:11:40 by cchameyr          #+#    #+#             */
/*   Updated: 2017/08/08 15:54:58 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define TINY_SIZE 100
# define SMALL_SIZE 1024
# define LARGE 1

# define USED 1
# define FREE 0

# define PROT PROT_WRITE|PROT_READ
# define MAP MAP_ANONYMOUS|MAP_PRIVATE

//debug
#include "../../Perso/debug.h"

typedef struct		s_map
{
	void			*tiny;
	void			*small;
	size_t			max_size;
}					t_map;

typedef struct		s_block
{
	size_t			size;
	struct s_block	*next;
	struct s_block	*back;
	int				status;
	void			*ptr;
}					t_block;


void	show_alloc_mem();

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);



#endif
