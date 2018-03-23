/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:18:31 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/23 10:46:24 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/header.h"
#include <stdio.h>

int		ft_strlen(const char *str)
{
	int i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

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

	int        i;
	size_t    j;
	char    *s;


	i = 0;
	j = 1024;
	while (i < (int)j)
	{
		s = (char*)malloc(j);
		s[0] = 42;
		free(s);
		i++;
	}
//	show_alloc_mem();
	return (0);

	
	/*	
		char *str1;
		char *str2;
		char *str3;
		char *str4;

		str1 = ft_strdup_perso("aaaaaaaaaaa");
		str2 = ft_strdup_perso("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
		str3 = ft_strdup_perso("fffffffffff");
		str4 = ft_strdup_perso("fffffffffffffffffffffffffff");
		show_alloc_mem();

		free(str2);
		show_alloc_mem();

		str2 = ft_strdup_perso("aaaaaa");
		show_alloc_mem();

		free(str4);
		str4 = ft_strdup_perso("ddddddd");
		show_alloc_mem();

		free(str3);
		show_alloc_mem();

*/	return 1;
}
