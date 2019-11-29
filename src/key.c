/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:06:31 by rostroh           #+#    #+#             */
/*   Updated: 2019/11/29 16:37:29 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void			print_key(const uint8_t *key, int keysz)
{
	int			i;

	i = 0;
	printf("Key : ");
	while (i < keysz)
	{
		printf("%02X ", key[i]);
		i++;
	}
	printf("\n");
}

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
			return (ft_error_parsing("key hex"));
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
	while (i + 1 < len)
	{
		key[j] = char_to_nibble(new[i]) << 4 | char_to_nibble(new[i + 1]);
		j++;
		i += 2;
	}
	if (i == len - 1)
		key[j] = char_to_nibble(new[i]);
	return (key);
}

uint8_t		*random_key_gen(int *keysz)
{
	int			i;
	uint8_t		*key;
	int			urand_stream;

	i = 0;
	if (!(key = (uint8_t *)malloc(sizeof(uint8_t) * DEFAULT_KEY_SIZE)))
		return (NULL);
	if ((urand_stream = open("/dev/urandom", O_RDONLY)) < 0)
	{
		printf("%s", ERROR_OPEN_URANDOM);
		return (NULL);
	}
	while (i < DEFAULT_KEY_SIZE)
	{
		if (read(urand_stream, &key[i], 1) < 0)
		{
			printf("%s", ERROR_READ_URANDOM);
			return (NULL);
		}
		i++;
	}
	*keysz = DEFAULT_KEY_SIZE;
	print_key(key, *keysz);
	return (key);
}
