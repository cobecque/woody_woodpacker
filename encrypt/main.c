/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:51:28 by rostroh           #+#    #+#             */
/*   Updated: 2019/10/24 17:42:17 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#define KEY_LEN 2
#define VERB 2

#if VERB == 1
	unsigned char		*rc4(const char *plain, const void *key, int size, int len);
#elif VERB == 2
	uint8_t				rc4(const char *plain, const void *key, int size, int len);
#else
	unsigned char				*rc4(const char *plain, const void *key, int size, int len);
#endif

unsigned char		*ft_strcpy(unsigned char *dst, const char *src)
{
	int			i;

	i = 0;
	while (src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

int			main(void)
{
	unsigned char		*str;
	unsigned char		*key;
	unsigned char		*whip;
	uint8_t					val;

	key = (unsigned char *)malloc(sizeof(unsigned char) * 2);
	str = (unsigned char *)malloc(sizeof(unsigned char) * 256);
	whip = (unsigned char *)malloc(sizeof(unsigned char) * 6);
	//whip = ft_strcpy(whip, "salut");
	whip[0] = 0x18;
	whip[1] = 0xe6;
	whip[2] = 0xa5;
	whip[3] = 0x5e;
	whip[4] = 0xa7;
	//printf("MDR %s\n", whip);
	key[0] = 0x10;
	key[1] = 0x64;
#if VERB == 1
	str = rc4((char *)whip, (void *)key, KEY_LEN, 5);
#elif VERB == 2
	val = rc4("salut", (void *)key, KEY_LEN, 5);
#else
	printf("Doute\n");
	str = rc4("salut", (void *)key, KEY_LEN, 5);
	printf("Doute 2\n");
#endif
	printf("Pas drole\n");
#if VERB == 1
	for (int i = 0; i < 256; i++)
		printf("%d\n", str[i]);
#elif VERB == 2
	printf("%d\n", val);
#else
	printf("MDR\n");
	int		i = 0;
	while (i < 5)
	{
		printf("%c ", str[i]);
		i++;
	}
	printf("\n");
#endif
	return (0);
}
