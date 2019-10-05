/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 06:43:18 by cobecque          #+#    #+#             */
/*   Updated: 2019/10/05 15:07:03 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"
#include <stdio.h>
#include <stdlib.h>
#include "sys/mman.h"

#define buff_size 1

void		init_env(t_env *env, char *file)
{
	int		fd;
	char	buff[buff_size];
	int		ret;
	int		i;
	int		off;

	i = 0;
	ft_bzero(env, sizeof(env));
	env->file = NULL;
	if ((fd = open(file, O_RDONLY)) != -1)
	{
		off = lseek(fd, 0, SEEK_END);
		env->file = malloc(off + i);
		off = lseek(fd, 0, SEEK_SET);
		while ((ret = read(fd, &buff, buff_size)) > 0)
		{
			ft_memcpy(env->file + i, &buff, ret);
			i += ret;
		}
		close(fd);
	}
}

int			main(int ac, char **av)
{
	t_env		e;
	int			i;
	Elf64_Sym	**sym;
	int			nb_sym;
	int			j;
	
	i = 0;
	if (ac != 2)
		return (0);
	init_env(&e, av[1]);
	if (e.file != NULL)
	{
		e.header = e.file;
		printf("SECTION HEADER :\n");
		e.phdr = (Elf64_Phdr **)malloc(sizeof(Elf64_Phdr *) * e.header->e_phnum);
		while (i < e.header->e_phnum)
		{
			e.phdr[i] = e.file + e.header->e_phoff + (e.header->e_phentsize * i);
			printf("type = %d offset = %lx\n", e.phdr[i]->p_type, e.phdr[i]->p_offset);
			i++;
		}
		printf("\n\nSECTION :\n");
		i = 0;
		e.shdr = (Elf64_Shdr **)malloc(sizeof(Elf64_Shdr *) * e.header->e_shnum);
		while (i < e.header->e_shnum)
		{
			e.shdr[i] = e.file + e.header->e_shoff + (e.header->e_shentsize * i);
			printf("%2d : type = %d offset = %lx\n", i, e.shdr[i]->sh_type, e.shdr[i]->sh_offset);
			if (e.shdr[i]->sh_type == SHT_SYMTAB)
			{
				printf("\nSection's symbol\n");
				nb_sym = e.shdr[i]->sh_size / sizeof(Elf64_Sym);
				sym = (Elf64_Sym **)malloc(sizeof(Elf64_Sym *) * nb_sym);
				j = 0;
				while (j < nb_sym)
				{
					sym[j] = e.file + e.shdr[i]->sh_offset + sizeof(Elf64_Sym) * j;
					printf("%2d : idx = %6d et type_symbol = %d\n", j, sym[j]->st_shndx, sym[j]->st_info);
					j++;
				}
				printf("\nEnd of symbol\n\n");
			}
			else if (e.shdr[i]->sh_type == SHT_DYNSYM)
				printf("Cool\n");
			i++;
		}
	}
	return (0);
}

