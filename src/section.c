/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:54:17 by rostroh           #+#    #+#             */
/*   Updated: 2019/11/29 16:37:43 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void			change_shdr(t_env *e)
{
	Elf64_Shdr *shdr;
	Elf64_Shdr loader;
	int			i;
	int			last;
	int			off;
	int			shdrnx;

	i = 0;
	last = 0;
	shdr = malloc(sizeof(Elf64_Shdr));
	e->header->e_shoff += 64;
	ft_bzero(&loader, sizeof(Elf64_Shdr));
	shdr = e->fwoody.content + e->header->e_shoff + e->header->e_shentsize * e->header->e_shstrndx;
	shdrnx = shdr->sh_offset + 64;
	while (i < e->header->e_shnum)
	{
		off = e->header->e_shoff + e->header->e_shentsize * i;
		shdr = e->fwoody.content + off;
		if (last != 0)
		{
			shdr->sh_offset += 64;
			memcpy(e->fwoody.content + off, shdr, sizeof(Elf64_Shdr));
		}
		if (ft_strcmp(".bss", (char *)e->fwoody.content + shdrnx + shdr->sh_name) == 0)
			last = i;
		i++;
	}
	off = e->header->e_shoff + e->header->e_shentsize * e->header->e_shnum;
	loader.sh_name = 0;
	loader.sh_type = SHT_PROGBITS;
	loader.sh_flags = SHF_ALLOC | SHF_EXECINSTR;
	loader.sh_addr = e->end_load_addr;
	loader.sh_offset = e->end_load_off;
	loader.sh_size = 64;
	loader.sh_link = 0;
	loader.sh_info = 0;
	loader.sh_addralign = 16;
	loader.sh_entsize = 0;
	memcpy(e->fwoody.content + off, &loader, sizeof(Elf64_Shdr));
}

void			add_section(t_env *e)
{
	uint64_t	addr;
	void		*cpy_memory_section;
	size_t		size;
	int			off;

	off = e->end_load_off;
	size = e->file.size - e->end_load_off;
	cpy_memory_section = (void *)malloc(size);
	memcpy(cpy_memory_section, e->file.content + off, size);
	memset(e->fwoody.content + off, 0, size);
	memset(e->fwoody.content + off, 0xe9, 1);
	addr = e->old_entry - (e->end_load_addr + 0x05);
	memcpy(e->fwoody.content + off + 0x01, &addr, 4);
	memcpy(e->fwoody.content + off + 64, cpy_memory_section, size);
}

void			change_phdr(t_env *e)
{
	Elf64_Phdr	*phdr;
	int			i;
	int			off;
	int			last;

	i = 0;
	phdr = malloc(sizeof(Elf64_Phdr));
	while (i < e->header->e_phnum)
	{
		off = e->header->e_phoff + e->header->e_phentsize * i;
		phdr = e->file.content + off;
		if (phdr->p_type == PT_LOAD)
			last = i;
		i++;
	}
	off = e->header->e_phoff + e->header->e_phentsize * last;
	phdr = e->file.content + off;
	e->end_load_off = phdr->p_offset + phdr->p_memsz;
	e->end_load_addr = phdr->p_vaddr + phdr->p_memsz;
	printf("%lx %lx\n", e->end_load_addr, e->end_load_off);
	phdr->p_filesz += 64;
	phdr->p_memsz += 64;
	phdr->p_flags |= PF_X;
	memcpy(e->fwoody.content + off, phdr, sizeof(Elf64_Phdr));
}

void			creat_new_section(t_env *e)
{
//	int		fd;

	e->fwoody.size = e->file.size + e->header->e_shentsize + 64; // size of section + size for code
	if (!(e->fwoody.content = (void *)malloc(e->fwoody.size)))
		return ;
	memcpy(e->fwoody.content, e->file.content, e->file.size);
	change_phdr(e);
	add_section(e);
	change_shdr(e);
	e->header->e_shnum += 1;
	e->header->e_entry = e->end_load_addr;
	memcpy(e->fwoody.content, e->header, e->header->e_ehsize);/*
	fd = open("woody", O_CREAT | O_RDWR, 0777);
	e->fwoody = encrypt_woody(e);
	write(fd, (char *)e->fwoody.content, e->fwoody.size);
	close(fd);*/
}
