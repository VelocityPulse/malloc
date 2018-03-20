/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:18:31 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/20 16:24:39 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/header.h"
#include <stdio.h>

char	*ft_strdup_perso(const char *s1)
{
	int		cpt;
	char	*s2;

	cpt = 0;
	s2 = malloc((ft_strlen(s1)));
	if (!s2)
		return (NULL);
	while (s1[cpt])
	{
		s2[cpt] = s1[cpt];
		cpt++;
	}
	s2[cpt] = '\0';
	return (s2);
}

int main()
{
	
	char *str1;
	char *str2;
	char *str3;
	char *str4;


/*	str1 = ft_strdup_perso("aaaaaaaaaaaaaaaaa");
	str2 = ft_strdup_perso("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	str3 = ft_strdup_perso("ccccccccccccccccc");
	show_alloc_mem();
	free(str2);
	show_alloc_mem();
	str2 = ft_strdup_perso("xx");
	str2 = ft_strdup_perso("xx");
	show_alloc_mem();
*/	return 1;
}
