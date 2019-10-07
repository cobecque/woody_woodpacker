/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:54:17 by rostroh           #+#    #+#             */
/*   Updated: 2019/10/07 15:22:23 by rostroh          ###   ########.fr       */
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

void			creat_new_section(t_env *e)
{
	int		fd;
	char	nb_sec;

	section_name(e);
	ft_memcpy(e->fwoody, e->file, sizeof(t_file_inf));
	e->fwoody.size += e_shentsize;
	e->fwoody.content[60] += 1;
	fd = open("woody", O_CREAT | O_RDWR, 0777);
	ft_putbin_fd(fd, (char *)e->file.content, e->file.size);;
	printf("--> %ld\n", e->header->e_shoff);
	lseek(fd, 60, SEEK_SET);
	nb_sec = e->header->e_shnum + 1;				//add one section to sh_num
	write(fd, &nb_sec, 1);
	lseek(fd, e->header->e_shentsize * e->header->e_shnum + e->header->e_shoff, SEEK_SET);
	for (int i = 0; i < e->header->e_shentsize; i++)
	{
		nb_sec = i;
		write(fd, &nb_sec, 1);
	}
	close(fd);
	//*(e->file + 60) += 0x1;
}

