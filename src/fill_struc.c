/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:32:57 by rostroh           #+#    #+#             */
/*   Updated: 2019/10/14 18:46:21 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*
** Set different verbose at 0 too mute them
*/
#define VERB 1
#if VERB == 1
# define DYN_VERB 0
# define SYM_VERB 0
# define HDR_VERB 0
# define SCT_VERB 1
#else                    //do not change that field
# define DYN_VERB 0
# define SYM_VERB 0
# define HDR_VERB 0
# define SCT_VERB 0
#endif

#define buff_size 1

void			init_env(t_env *env, char *file)
{
	int		fd;
	char	buff[buff_size];
	int		ret;
	int		i;
	int		off;

	i = 0;
	ft_bzero(env, sizeof(env));
	env->file.content = NULL;
	if ((fd = open(file, O_RDONLY)) != -1)
	{
		off = lseek(fd, 0, SEEK_END);
		env->file.size = off;
		env->file.content = malloc(off + i);
		off = lseek(fd, 0, SEEK_SET);
		while ((ret = read(fd, &buff, buff_size)) > 0)
		{
			ft_memcpy(env->file.content + i, &buff, ret);
			i += ret;
		}
		close(fd);
	}
	else
		printf("%s: No such file or directory\n", file);
}

void			fill_program_header(t_env *e)
{
	int			i;

	i = 0;
	if (HDR_VERB == 1)
		printf("PROGRAM HEADER:\n");
	e->phdr = (Elf64_Phdr **)malloc(sizeof(Elf64_Phdr *) * e->header->e_phnum);
	while (i < e->header->e_phnum)
	{
		e->phdr[i] = e->file.content + e->header->e_phoff + (e->header->e_phentsize * i);
		if (HDR_VERB == 1)
			printf("type = %d offset = %lx\n", e->phdr[i]->p_type, e->phdr[i]->p_offset);
		i++;
	}
}

static void		fill_symbol(t_env *e, int i, char *type_sec)
{
	int			j;
	int			nb_sym;

	j = 0;
	if (SYM_VERB == 1)
		printf("\nSection's %s\n", type_sec);
	nb_sym = e->shdr[i]->sh_size / sizeof(Elf64_Sym);
	e->sym = (Elf64_Sym **)malloc(sizeof(Elf64_Sym *) * nb_sym);
	while (j < nb_sym)
	{
		e->sym[j] = e->file.content + e->shdr[i]->sh_offset + sizeof(Elf64_Sym) * j;
		if (SYM_VERB == 1)
			printf("%2d : idx = %6d, name_idx = %d  et type_symbol = %d\n", j, e->sym[j]->st_shndx, e->sym[j]->st_name, e->sym[j]->st_info);
		j++;
	}
	if (SYM_VERB == 1)
		printf("\nEnd of symbol\n\n");
}

void			fill_dynamics(t_env *e, int i)
{
	int		j;
	int		nb_dyn;

	j = 0;
	nb_dyn = e->shdr[i]->sh_size / sizeof(Elf64_Dyn);
	if (!(e->dyn = (Elf64_Dyn **)malloc(sizeof(Elf64_Dyn *) * nb_dyn)))
		return ;
	if (DYN_VERB == 1)
		printf("\n\nDynamic:\n");
	while (j < nb_dyn)
	{
		e->dyn[j] = e->file.content + e->shdr[i]->sh_offset + sizeof(Elf64_Dyn) * j;
		if (DYN_VERB == 1)
			printf("%d : val = %lu\n", j, e->dyn[j]->d_un.d_val);
		if (e->dyn[j]->d_tag == DT_NULL)
			break ;
		j++;
	}
	if (DYN_VERB == 1)
		printf("\n\n");
	//	printf("nb_dyn = %d, 0x%lx\n", nb_dyn, (unsigned long)e->shdr[i]->sh_offset);
}

void			fill_section_header(t_env *e)
{
	int			i;

	i = 0;
	if (SCT_VERB == 1)
		printf("\n\nSECTION HEADER:\n");
	e->shdr = (Elf64_Shdr **)malloc(sizeof(Elf64_Shdr *) * e->header->e_shnum + 1);
	while (i < e->header->e_shnum)
	{
		e->shdr[i] = e->file.content + e->header->e_shoff + (e->header->e_shentsize * i);
		if (SCT_VERB == 1)
			printf("%2d : offset = %lx, size = %lx et name_idx = %d\n", i, e->shdr[i]->sh_offset, e->shdr[i]->sh_size, e->shdr[i]->sh_name);
		if (e->shdr[i]->sh_type == SHT_SYMTAB)
			fill_symbol(e, i, "symbols");
		else if (e->shdr[i]->sh_type == SHT_DYNSYM)
			fill_symbol(e, i, "dynsyms");
		else if (e->shdr[i]->sh_type == SHT_DYNAMIC)
			fill_dynamics(e, i);
		i++;
	}
}


