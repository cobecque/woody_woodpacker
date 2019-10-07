/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:54:17 by rostroh           #+#    #+#             */
/*   Updated: 2019/10/07 19:57:02 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"
/*
void			fill_section_header(t_env *e)
{
	int			i;

	i = 0;
	if (SCT_VERB == 1)
		printf("\n\nSECTION HEADER:\n");
	e->shdr = (Elf64_Shdr **)malloc(sizeof(Elf64_Shdr *) * e->header->e_shnum);
	while (i < e->header->e_shnum)
	{
		e->shdr[i] = e->file + e->header->e_shoff + (e->header->e_shentsize * i);
		if (SCT_VERB == 1)
			printf("%2d : offset = %lx, size = %lx\n", i, e->shdr[i]->sh_offset, e->shdr[i]->sh_size);
		if (e->shdr[i]->sh_type == SHT_SYMTAB)
			fill_symbol(e, i, "symbols");
		else if (e->shdr[i]->sh_type == SHT_DYNSYM)
			fill_symbol(e, i, "dynsyms");
		else if (e->shdr[i]->sh_type == SHT_DYNAMIC)
			fill_dynamics(e, i);
		i++;
	}
}*/
void			ft_putbin_fd(int fd, char *str, size_t size)
{
	write(fd, str, size);
}

void			section_name(t_env *e)
{
	int					i;
//	int					size;
	unsigned long		offset;

	i = 0;
	//size = 0;
	offset = e->shdr[e->header->e_shstrndx]->sh_offset;
	printf("Offset = %lx\n", offset);
	while (i < e->header->e_shnum)
	{
	//	size = find_next_name(e);
		printf("%s\n", (char *)(e->file.content + offset + e->shdr[i]->sh_name));
		//ft_putbin_fd(1, (char *)(e->file.content + offset + size), size);
		//ft_putbin_fd(1, (char *)(e->file.content + offset + e->shdr[i]->sh_name), e->shdr[i]->sh_name - size);
		//printf("size = %d\n", e->shdr[i]->sh_name - size);
		//size += e->shdr[i]->sh_name;
		i++;
	}
}

void			shift_section(t_env *e)
{
	memset(e->fwoody.content + e->header->e_shoff, 0, 16);
	memcpy((char *)e->fwoody.content + e->shdr[e->header->e_shstrndx]->sh_offset + e->shdr[e->header->e_shstrndx]->sh_size, ".loader", 7);
	e->header->e_shoff += 16;
}

void			creat_new_section(t_env *e)
{
	int				fd;
	int				i;
	Elf64_Shdr		loader;

	i = 0;
	e->fwoody.size = e->file.size + e->header->e_shentsize + 16;
	if (!(e->fwoody.content = (void *)malloc(e->fwoody.size)))
		return ;
	printf("coucou\n");
	memcpy(e->fwoody.content, e->file.content, e->file.size);//e->file.size);
	e->header->e_shnum += 1;
	e->fwoody.size = e->file.size + e->header->e_shentsize + 16;
	fd = open("woody", O_CREAT | O_RDWR, 0777);
	ft_memcpy(&loader, e->shdr[30], sizeof(Elf64_Shdr));
	loader.sh_name = e->shdr[e->header->e_shstrndx]->sh_size;
	loader.sh_type = SHT_NULL;
	loader.sh_flags = SHF_ALLOC | SHF_EXECINSTR;
	loader.sh_addr = 0;
	loader.sh_offset = 0;
	loader.sh_size = 0;
	loader.sh_link = 0;
	loader.sh_info = 0;
	loader.sh_addralign = 0;
	loader.sh_entsize = 0;
	shift_section(e);
	e->shdr[e->header->e_shstrndx]->sh_size += 16;
	e->shdr[e->header->e_shnum - 1] = &loader;
	while (i <= e->header->e_shnum - 1)
	{
		memcpy(e->fwoody.content + e->header->e_shoff + (e->header->e_shentsize * i), e->shdr[i], e->header->e_shentsize);
		printf("%d %d %lx %lx\n", i, e->shdr[i]->sh_name, e->header->e_shoff + (e->header->e_shentsize * i), e->shdr[i]->sh_offset);
		i++;
	}
	memcpy(e->fwoody.content, e->header, e->header->e_ehsize);
	ft_putbin_fd(fd, (char *)e->fwoody.content, e->fwoody.size);
	close(fd);
}

