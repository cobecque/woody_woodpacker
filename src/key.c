/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:06:31 by rostroh           #+#    #+#             */
/*   Updated: 2019/10/14 21:03:39 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

int				check_key(unsigned char *key)
{
	int			i;

	i = 0;
	while (key[i] != '\0')
	{
		if ((key[i] >= '0' && key[i] <= '9') || (key[i] >= 'a' && key[i] <= \
			'f') || (key[i] >= 'A' && key[i] <= 'F') || key[i] == ' ')
			;
		else
		{
			printf("Key must contains hexadecimal values only\n");
			return (-1);
		}
		i++;
	}
	return (1);
}

char			char_to_nibble(char val)
{
	if (val >= '0' && val <= '9')
		return (val - '0');
	if (val >= 'a' && val <= 'f')
		return (val - 'a' + 10);
	if (val >= 'A' && val <= 'F')
		return (val - 'A' + 10);
	return (0);
}

unsigned char	*clear_space(unsigned char *entry, int *size)
{
	int				i;
	int				j;
	unsigned char	*new;

	i = 0;
	j = 0;
	while (entry[i] != '\0')
	{
		if (entry[i] != ' ')
			j++;
		i++;
	}
	if (!(new = (unsigned char *)malloc(sizeof(unsigned char) * j + 1)))
		return (NULL);
	i = 0;
	while (entry[i] != '\0')
	{
		if (entry[i] != ' ')
		{
			new[*size] = entry[i];
			printf("%c",new[*size]);
			(*size)++;
		}
		i++;
	}
	new[*size] = '\0';
	return (new);
}

uint8_t			*key_to_hexa(unsigned char *entry, int *size)
{
	int				i;
	int				j;
	int				len;
	uint8_t			*key;
	unsigned char	*new;

	i = 0;
	j = 0;
	new = clear_space(entry, size);
	*size = *size / 2 + *size % 2;
	if (!(key = (uint8_t *)malloc(sizeof(uint8_t) * *size)))
		return (NULL);
	len = _ft_strlen((char *)new);
	printf("Doute %d\n", len);
	while (i + 1 < len)
	{
		key[j] = char_to_nibble(new[i]) << 4 | char_to_nibble(new[i + 1]);
		printf("%x ", key[j]);
		j++;
		i += 2;
	}
	if (i == len - 1)
	{
		key[j] = char_to_nibble(new[i]);
		printf("%x ", key[j]);
	}
	return (key);
}
