/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 06:43:18 by cobecque          #+#    #+#             */
/*   Updated: 2019/10/06 12:36:09 by rostroh          ###   ########.fr       */
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

void		fill_section_header(t_env *e)
{
	int			i;

	i = 0;
	printf("SECTION HEADER :\n");
	e->phdr = (Elf64_Phdr **)malloc(sizeof(Elf64_Phdr *) * e->header->e_phnum);
	while (i < e->header->e_phnum)
	{
		e->phdr[i] = e->file + e->header->e_phoff + (e->header->e_phentsize * i);
		printf("type = %d offset = %lx\n", e->phdr[i]->p_type, e->phdr[i]->p_offset);
		//if (e->phdr[i].p_type == PT_DYNAMIC)
		//	printf("\t\t--> C%d\n", 
		i++;
	}
}

void		fill_section(t_env *e, int i, char *type_sec)
{
	int			j;
	int			nb_sym;

	j = 0;
	printf("\nSection's %s\n", type_sec);
	nb_sym = e->shdr[i]->sh_size / sizeof(Elf64_Sym);
	e->sym = (Elf64_Sym **)malloc(sizeof(Elf64_Sym *) * nb_sym);
	while (j < nb_sym)
	{
		e->sym[j] = e->file + e->shdr[i]->sh_offset + sizeof(Elf64_Sym) * j;
		printf("%2d : idx = %6d, name_idx = %d  et type_symbol = %d\n", j, e->sym[j]->st_shndx, e->sym[j]->st_name, e->sym[j]->st_info);
		j++;
	}
	printf("\nEnd of symbol\n\n");
}

void		fill_dynamics(t_env *e, int i)
{
	int		j;
	int		nb_dyn;

	j = 0;
	nb_dyn = e->shdr[i]->sh_size / sizeof(Elf64_Dyn);
	if (!(e->dyn = (Elf64_Dyn **)malloc(sizeof(Elf64_Dyn *) * nb_dyn)))
	{
		printf("MDR !\n");
		return ;
	}
	printf("\n\nDynamic:\n");
	while (j < nb_dyn)
	{
		e->dyn[j] = e->file + e->shdr[i]->sh_offset + sizeof(Elf64_Dyn) * j;
		printf("%d : val = %lu\n", j, e->dyn[j]->d_un.d_val);
		if (e->dyn[j]->d_tag == DT_NULL)
			break ;
		j++;
	}
	printf("\n\n");
	//	printf("nb_dyn = %d, 0x%lx\n", nb_dyn, (unsigned long)e->shdr[i]->sh_offset);
}

void		fill_section_table(t_env *e)
{
	int			i;

	i = 0;
	printf("\n\nSECTION :\n");
	e->shdr = (Elf64_Shdr **)malloc(sizeof(Elf64_Shdr *) * e->header->e_shnum);
	while (i < e->header->e_shnum)
	{
		e->shdr[i] = e->file + e->header->e_shoff + (e->header->e_shentsize * i);
		printf("%2d : type = %d offset = %lx\n", i, e->shdr[i]->sh_type, e->shdr[i]->sh_offset);
		if (e->shdr[i]->sh_type == SHT_SYMTAB)
			fill_section(e, i, "symbols");
		else if (e->shdr[i]->sh_type == SHT_DYNSYM)
			fill_section(e, i, "dynsyms");
		else if (e->shdr[i]->sh_type == SHT_DYNAMIC)
			fill_dynamics(e, i);
		i++;
	}
}

int			main(int ac, char **av)
{
	t_env		e;

	if (ac != 2)
		return (0);
	init_env(&e, av[1]);
	if (e.file != NULL)
	{
		e.header = e.file;
		fill_section_header(&e);
		fill_section_table(&e);
		printf("OEP = 0x%lx str_dx = %d\n", e.header->e_entry, e.header->e_shstrndx);
	}
	return (0);
}

//printf("%d, %d, %d, %d, %d, %d, %d\n", SHN_UNDEF, SHN_LORESERVE, SHN_LOPROC, SHN_HIPROC, SHN_ABS, SHN_COMMON, SHN_HIRESERVE);
