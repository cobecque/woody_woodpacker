/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 19:18:05 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/02 20:11:54 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int			_size = 256;

int			compare(char *s1, int idx, char *s2)
{
	int		i = 0;
	//int		count = 0;

	while (s1[idx + i] != '\0')
	{
		if (s1[idx + i] != s2[i])
			break ;
		i++;
	}
	return (i);
}

int			find_occur(char *str, int idx, char **dico)
{
	int		nb = 0;
	int		latest = -1;

	for (int i = 0; i < _size; i++)
	{
		if (compare(str, idx, dico[i]) > nb)
		{
			nb = compare(str, idx, dico[i]);
			latest = i;
		}
	}
	printf("%d : ", latest);
	return (latest);
}

char		**ft_realloc(char **dico)
{
	char		**new;

	new = (char **)malloc(sizeof(char *) * _size);
	for (int i = 0; i < _size - 1; i++)
	{
		new[i] = (char *)malloc(sizeof(char) * strlen(dico[i]));
		strcpy(new[i], dico[i]);
		free(dico[i]);
	}
	free(dico);
	return (new);
}

char		**enlarge_dico(char **dico, char *str, int pos)
{
	int			len;

	len = strlen(dico[pos]) + 2;
	_size++;
	dico = ft_realloc(dico);
	dico[_size - 1] = (char *)malloc(sizeof(char) * len);
	for (int i = 0; i < len - 2; i++)
	{
		dico[_size - 1][i] = dico[pos][i];
	}
	dico[_size - 1][len - 2] = *(str + 1);
	dico[_size - 1][len - 1] = '\0';
/*	for (int i = 0; i < len; i++)
	{
		printf("%c", dico[_size - 1][i]);
	}
*/	printf("\n");
	return (dico);
}

void		encode(char *str, char **dico)
{
	int			pos;
	int			len;

	len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		printf("%d\n", i);
		if ((pos = find_occur(str, i, dico)) >= 0)
		{
			printf("Occurence founded\n");
			dico = enlarge_dico(dico, str + i, pos);
		}
		else
			printf("Add to dico\n");
	}
//	for (int i = 0; i < _size; i++)
//		printf("%d : %s\n", i, dico[i]);
}

void		init_dico(char **dico)
{
	int		i;

	i = 0;
	while (i < 256)
	{
		dico[i] = (char *)malloc(sizeof(char) * 2);
		dico[i][0] = i;
		dico[i][1] = '\0';
		i++;
	}
}

int			main(void)
{
	char	*str;
	char	**dico;

	str = strdup("BABAABAAA");//strdup("AAAAAABABABABAAAB");
	dico = (char **)malloc(sizeof(char *) * _size);
	init_dico(dico);
	encode(str, dico);
	return (0);
}

