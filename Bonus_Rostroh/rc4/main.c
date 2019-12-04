/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:04:39 by rostroh           #+#    #+#             */
/*   Updated: 2019/11/29 16:38:04 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 7

//unsigned char		*rc4(const void *key, int key_size, unsigned char *plain, int pain_len);
int					rc4(const void *key, int key_size, unsigned char *plain, int pain_len);

int			main(void)
{
	int				len;
	unsigned char	*str;
	unsigned char	key[SIZE];
	unsigned char	*tab;
	int				res;

	str = (unsigned char *)strdup("The quick brown fox jumps over the lazy dog.");
	tab = (unsigned char *)malloc(sizeof(char) * 256);
	len = strlen((char *)str);
	printf("-> %s %d\n", str, len);
	key[0] = 0x63;
	key[1] = 0x72;
	key[2] = 0x79;
	key[3] = 0x70;
	key[4] = 0x74;
	key[5] = 0x69;
	key[6] = 0x69;
	//tab = rc4(key, SIZE, str, len);
	res = rc4(key, SIZE, str, len);
	printf("Toujours debout\n");
	//for (int i = 0; i < 256; i++)
	//	printf("%d = %d\n", i, tab[i]);
	printf("%d\n", res);
	for (int i = 0; i < len; i++)
		printf("%X ", str[i]);
	printf("\n");
	return (0);
}
