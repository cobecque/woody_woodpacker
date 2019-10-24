/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:23:30 by rostroh           #+#    #+#             */
/*   Updated: 2019/10/24 16:56:27 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../includes/libft.h"
#include "../includes/libftasm.h"

#define SIZE_PERM 256
#define PLAIN var.plain_txt
#define S(x) var.perm[x]

typedef struct		s_key
{
	int				len;
	unsigned char	*key;
}					t_key;

typedef struct		s_rc4
{
	t_key			key_inf;
	unsigned char	perm[SIZE_PERM];
	uint8_t			*plain_txt;
	int				size_txt;
}					t_rc4;

int				check_key(unsigned char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f') || (str[i] >= 'A' && str[i] <= 'F')))
		{
			printf("Key contains non-hexadecimal values\n");
			return (-1);
		}
		i++;
	}
	return (1);
}

char				char_to_nibble(char val)
{
	if (val >= '0' && val <= '9')
		return (val - '0');
	if (val >= 'a' && val <= 'f')
		return (val  - 'a' + 10);
	if (val >= 'A' && val <= 'F')
		return (val  - 'A' + 10);
	return (0);
}

t_key				get_key(unsigned char *entry, int entry_size)
{
	int				i;
	int				j;
	t_key			nk;

	i = 0;
	j = 0;
	if (!(nk.key = (unsigned char *)malloc(sizeof(unsigned char) * entry_size / 2 + entry_size % 2)))
		return (nk);
	while (i + 1 < entry_size)
	{
		if (entry[i] != ' ' && entry[i + 1] != ' ')
		{
			nk.key[j] = char_to_nibble(entry[i]) << 4 | char_to_nibble(entry[i + 1]);
			printf("%x ", nk.key[j]);
			j++;
			i += 2;
		}
		else
			i++;
	}
	if (i == entry_size - 1)
	{
		nk.key[j] = char_to_nibble(nk.key[i]);
		j++;
	}
	printf("\n");
	nk.len = j;
	return (nk);
}

int				parsing_rc4(int nb_entry, char **entry, t_rc4 *var)
{
	int			inf;

	inf = 0;
	var->key_inf = get_key((unsigned char *)entry[3 + inf], ft_strlen(entry[3 + inf]));
	for (int i = 0; i < SIZE_PERM; i++)
		var->perm[i] = i;
	var->plain_txt = (unsigned char *)entry[1 + inf];
	//printf("RC4 var:\n decode = %d\n size_key = %d\n key = %s\n plain_txt = %s\n", var->flg.f_decode, var->size_key, var->key, var->plain_txt);
	return (1);
}

void			swap(unsigned char *a, unsigned char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void			print_cypher(unsigned char *cypher)
{
	int			i;
	
	i = 0;
	while (cypher[i] != '\0')
	{
		printf("%x ", cypher[i]);
		i++;
	}
	printf("\n");
}

void			rc4(t_rc4 var)
{
	int		i;
	int		j;
	int		size;
	int		code_byte;
	unsigned char	*cypher;

	j = 0;
	//INIT PERMUTATION TABLE
	for (int i = 0; i < SIZE_PERM; i++)
	{
		j = (j + S(i) + var.key_inf.key[i % var.key_inf.len]) % SIZE_PERM;
		swap(&S(i), &S(j));
	//	printf("%d %d\n", S(i), S(j));
	}
	//PRINT PERMUTATION TABLE
	//for (int i = 0; i < SIZE_PERM; i++)
	//	printf("S(%d) = %d\n", i, S(i));
	size = ft_strlen((char *)PLAIN);
	i = 0;
	j = 0;
	cypher = (unsigned char *)malloc(sizeof(unsigned char) * size + 1);
	for (int k = 0; k < size; k++)
	{
		i = (i + 1) % SIZE_PERM;
		j = (j + S(i)) % SIZE_PERM;
		swap(&S(i), &S(j));
		code_byte = S((S(i) + S(j)) % SIZE_PERM);
		cypher[k] = code_byte ^ var.plain_txt[k];
		printf("%X pour %d\n", cypher[k], code_byte);
	}
	//printf("\n");
	//cypher[size] = '\0';
	//print_cypher(cypher);
	return ;
}

int				main(int argc, char **argv)
{
	t_rc4		var;

	if (argc != 4 && argc != 5)
		printf("Encode usage:\n ./rc4 <string> -K <key>\nDecode usage:\n ./rc4 -d <string> - K <key>\n:)\n");
	if (parsing_rc4(argc, argv, &var) == 1)
		rc4(var);
	return (0);
}

