#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern unsigned char	*_rc4();

int		calc_len(char *str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i] != 0)
	{
		if (str[i] != ' ')
			len++;
		i++;
	}
	return (len / 2);
}

uint8_t	ft_atoi_hex(char c)
{
	uint8_t	res;

	if (c >= 'a' && c <= 'f')
		res = c - 'a' + 10;
	else
		res = c - '0';
	return (res);
}

uint8_t	get_hex(char *str, int idx)
{
	uint8_t	result;


	result = ft_atoi_hex(str[idx]) * 16 + ft_atoi_hex(str[idx + 1]);
	return (result);
}

uint8_t		*pullout_string(char *str)
{
	int		i;
	int		j;
	int		len;
	uint8_t	*new;

	i = 0;
	j = 0;
	len = calc_len(str);
	//printf("\nlen = %d\n", len);
	new = (uint8_t*)malloc(sizeof(uint8_t) * len);
	while (i < len)
	{
		new[i] = get_hex(str, j);
		i++;
		j += 2;
		if (str[j] == ' ')
			j++;
	}
	return (new);
}

int		main(int argc, char **argv)
{
	uint8_t		key[16];
	uint8_t 	*plain;
	uint8_t		*distance;
	int		len;

	len = 0;
	key[0] = 0xAF;
	key[1] = 0xD1;
	key[2] = 0xDF;
	key[3] = 0xE1;
	key[4] = 0x43;
	key[5] = 0x9B;
	key[6] = 0x31;
	key[7] = 0xBB;
	key[8] = 0x79;
	key[9] = 0x3A;
	key[10] = 0x8D;
	key[11] = 0x58;
	key[12] = 0x83;
	key[13] = 0x6A;
	key[14] = 0x68;
	key[15] = 0xCE;
	
	if (argc == 1)
		printf("Need text\n");
	else
	{
		plain = pullout_string(argv[1]);
		len = calc_len(argv[1]);
		distance = (uint8_t *)malloc(sizeof(uint8_t) * len);
		printf("\n\nlen = %d\n", len);
		for (int i = 0; i < len; i++)
			printf("%02x ", plain[i]);
		printf("\n");
		_rc4(plain, key, 16, len, distance);
		//_rc4(key, 16, plain, len);
		printf("\n\nlen = %d\n", len);
		for (int i = 0; i < len; i++)
			printf("%02x ", distance[i]);
		printf("\n");
	}
	return (0);
}
