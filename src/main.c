/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 06:43:18 by cobecque          #+#    #+#             */
/*   Updated: 2019/10/14 21:00:43 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"
#include <stdio.h>
#include <stdlib.h>
#include "sys/mman.h"

int			fill_algo(int *algo_idx, char *algo)
{
	int			i;
	const char	*alg_name[] = {"rc4"};

	i = 0;
	if (algo[0] == '-')
	{
		if (_ft_strlen(algo) == 1)
		{
			printf("No algo specified\n");
			return (-1);
		}
		else
		{
			algo++;
			while (i < NB_ALGO)
			{
				if (ft_strcmp(alg_name[i], algo) == 0)
				{
					*algo_idx = i;
					break ;
				}
				i++;
			}
		}
	}
	else
	{
		*algo_idx = 0;
		return (1);
	}
	return (0);
}

t_parser	pars_information(int ac, char **av)
{
	int			exc;
	t_parser	inf;

	exc = 1;
	if (fill_algo(&inf.algo, av[exc]) != 1)
		exc++;
	if (exc < ac)
	{
		if (ft_strcmp(av[exc], "-k") == 0)
		{
			exc++;
			if (exc < ac)
				inf.key = av[exc];
			exc++;
		}
	}
	if (exc < ac)
		inf.exec = av[exc];
	else
		printf("No exec specified\n");
	return (inf);
}

int			init_rc4(t_rc4 *var, t_parser inf)
{
	var->key_len = 0;
	if (check_key((unsigned char *)inf.key) == -1)
		return (-1);
	var->key = key_to_hexa((unsigned char *)inf.key, &var->key_len);
	printf("--> %d\n", var->key_len);
	return (0);
}

int			main(int ac, char **av)
{
	t_env		e;
	t_rc4		var;
	t_parser	inf;

	if (ac <= 1 || ac > 5)
	{
		printf("Usage: ./woody_woodypacker -[algo] -k [key] <executable\n\tAlgo : rc4\nDefault : rc4 with randomly genereted key\n");
		return (0);
	}
	inf = pars_information(ac, av);
	if (!inf.exec)
		return (0);
	printf("algo = %d\nkey = %s\nexec = %s\n", inf.algo, inf.key, inf.exec);
	if (init_rc4(&var, inf) == -1)
		return (0);
	init_env(&e, inf.exec);
	if (e.file.content != NULL)
	{
		e.header = e.file.content;
		fill_program_header(&e);
		fill_section_header(&e);
		//printf("OEP = 0x%lx entsize = %d strndx = %d, shoff = %lx\n", e.header->e_entry, e.header->e_shentsize, e.header->e_shstrndx, e.header->e_shoff);
		creat_new_section(&e);
	}
	return (0);
}

//printf("%d, %d, %d, %d, %d, %d, %d\n", SHN_UNDEF, SHN_LORESERVE, SHN_LOPROC, SHN_HIPROC, SHN_ABS, SHN_COMMON, SHN_HIRESERVE);
