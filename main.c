/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:18:31 by cchameyr          #+#    #+#             */
/*   Updated: 2018/03/19 12:19:04 by cchameyr         ###   ########.fr       */
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

	str1 = ft_strdup_perso("abcdefghijklmnopqrstwxyz123");
	str2 = ft_strdup_perso("aaaaaaaaaaaaaaaa");
	str3 = ft_strdup_perso("abcd");

	printf("%s\n", str1);
	printf("%s\n", str2);
	printf("%s\n", str3);
	printf("sizeof(size_t) : %lu\n", sizeof(size_t));
	printf("sizeof(t_block) : %lu\n", sizeof(t_block));
	show_alloc_mem();

	return 1;
}
