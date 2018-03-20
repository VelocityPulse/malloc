/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:18:31 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/20 15:14:43 by cchameyr         ###   ########.fr       */
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

	ft_strdup_perso("aaaaaaaaaaaaaaaaa");
	str1 = ft_strdup_perso("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	str2 = ft_strdup_perso("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	str3 = ft_strdup_perso("vvvvvvvvvvvvvvvv");
	show_alloc_mem();
	DEBUG
	free(str2);
	show_alloc_mem();
	free(str3);
	show_alloc_mem();
	DEBUG
	ft_strdup_perso("aaaa");
	ft_strdup_perso("bbbbb");
	ft_strdup_perso("bbbb");
	show_alloc_mem();

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
