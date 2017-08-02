/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 12:11:40 by cchameyr          #+#    #+#             */
/*   Updated: 2017/08/02 13:57:52 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>
# include <stdlib.h>


void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);



#endif
