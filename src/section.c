/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:54:17 by rostroh           #+#    #+#             */
/*   Updated: 2019/10/07 18:09:27 by rostroh          ###   ########.fr       */
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
	uint32_t		size;
	void			*sh_cpy;

	sh_cpy = malloc(e->header->e_shentsize * e->header->e_shnum);
	ft_memcpy(sh_cpy, e->file.content + e->header->e_shoff, e->header->e_shentsize * e->header->e_shnum);
	memset(e->fwoody.content + e->header->e_shoff, 0, 16);
	ft_memcpy(e->fwoody.content + e->shdr[e->header->e_shstrndx]->sh_offset + e->shdr[e->header->e_shstrndx]->sh_size, ".loader", 7);
	size = e->shdr[e->header->e_shstrndx]->sh_size + 16;
	e->header->e_shoff += 16;
	ft_memcpy(e->fwoody.content + e->header->e_shoff + e->header->e_shentsize * e->header->e_shstrndx + 32, &size, sizeof(uint32_t));
	printf("--> %x %lx\n", size, e->header->e_shoff + e->header->e_shentsize * e->header->e_shstrndx + 32);
	ft_memcpy(e->fwoody.content + e->header->e_shoff, sh_cpy, e->header->e_shentsize * e->header->e_shnum);
}

void			creat_new_section(t_env *e)
{
	int				fd;
	int				i;
	//Elf64_Shdr		loader;

	i = 0;
	//section_name(e);
	e->fwoody.size = e->file.size + e->header->e_shentsize + 16;
	if (!(e->fwoody.content = (void *)malloc(e->fwoody.size)))
		return ;
	printf("coucou\n");
	ft_memcpy(&e->fwoody, &e->file, sizeof(t_file_inf));//e->file.size);
	memset(e->fwoody.content + 60, e->header->e_shnum + 1, 1);
	e->fwoody.size = e->file.size + e->header->e_shentsize + 16;
	fd = open("woody", O_CREAT | O_RDWR, 0777);
	//ft_memcpy(&loader, e->shdr[30], sizeof(Elf64_Shdr));
//	ft_memcpy(e->fwoody.content + e->file.size, &loader, sizeof(Elf64_Shdr));
	shift_section(e);
	//e->shdr[e->header->e_shnum - 1] = &loader;
	printf("-->%d\n", e->shdr[1]->sh_name);
	//LA FIN
	while (i < e->header->e_shnum - 1)
	{
		ft_memcpy(e->fwoody.content + e->header->e_shoff + e->header->e_shentsize * i, e->shdr[i], e->header->e_shentsize);
		printf("%d et %lx\n", e->shdr[i]->sh_name, e->header->e_shoff + e->header->e_shentsize * i);
		i++;
	}
	//memcpy(e->fwoody.content + e->header->e_shoff, e->shdr, e->header->e_shentsize * e->header->e_shnum);
	ft_putbin_fd(fd, (char *)e->fwoody.content, e->fwoody.size);
	close(fd);
}
/*
	lseek(fd, e->header->e_shentsize * e->header->e_shnum + e->header->e_shoff, SEEK_SET);
	for (int i = 0; i < e->header->e_shentsize; i++)
	{
		nb_sec = i;
		write(fd, &nb_sec, 1);
	}
	close(fd);
	*(e->file + 60) += 0x1;
}*/

