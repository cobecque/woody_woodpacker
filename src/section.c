/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:54:17 by rostroh           #+#    #+#             */
/*   Updated: 2019/10/11 12:32:15 by cobecque         ###   ########.fr       */
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
}

void			fill_loader_section(t_env *e, Elf64_Shdr *loader)
{
	int				last;
	int				i;
	int				size;
	void			*cpy_memory_section;

	i = 0;
	last = 0;
	while (i < e->header->e_shnum - 2)
	{
		if (e->shdr[i]->sh_type != SHT_NULL && e->shdr[i]->sh_addr == 0)
		{
			if (last == 0)
			{
				last = i - 1;
				//e->shdr[i]->sh_offset = e->shdr[last]->sh_offset + e->shdr[last]->sh_size + 64;
			}
			//else
			//	e->shdr[i]->sh_offset = e->shdr[i - 1]->sh_offset + e->shdr[i - 1]->sh_size;
		}
		i++;
	}
	loader->sh_addr = e->shdr[last]->sh_addr + e->shdr[last]->sh_size;
	loader->sh_offset = e->shdr[last]->sh_offset + e->shdr[last]->sh_size;
	loader->sh_name = e->shdr[e->header->e_shstrndx]->sh_size;
	loader->sh_type = SHT_PROGBITS;
	loader->sh_flags = SHF_ALLOC | SHF_EXECINSTR;
	loader->sh_size = 64;
	loader->sh_link = 0;
	loader->sh_info = 0;
	loader->sh_addralign = 16;
	loader->sh_entsize = 0;
	shift_section(e);
	size = e->header->e_shoff - e->shdr[last + 1]->sh_offset + 16;
	printf("size = %lx && offset comment %lx\n", (unsigned long)size, (unsigned long)e->shdr[last + 1]->sh_offset);
	cpy_memory_section = (void *)malloc(size);
	memcpy(cpy_memory_section, e->fwoody.content + e->shdr[last + 1]->sh_offset, size);
	memset(e->fwoody.content + e->shdr[last + 1]->sh_offset, 0, size);
	memset(e->fwoody.content + loader->sh_offset, 0xe9, sizeof(unsigned char));
	e->header->e_entry = e->header->e_entry - (loader->sh_addr + 5);
	printf("%lx %lx\n", (unsigned long)e->header->e_entry, (unsigned long)(loader->sh_addr + 5));
	memcpy(e->fwoody.content + loader->sh_offset + sizeof(unsigned char), (&e->header->e_entry), 4);
	memset(e->fwoody.content + loader->sh_offset + 5, 0xc3, 1);
	e->header->e_entry = loader->sh_addr;
	e->header->e_type = ET_EXEC;
	memcpy(e->fwoody.content + loader->sh_offset + loader->sh_size, cpy_memory_section, size);
	printf("loader off = %lx\n", (unsigned long)(loader->sh_offset));
	i = last + 1;
	e->shdr[i]->sh_offset = loader->sh_offset + loader->sh_size;
	printf("comment = %lx\n", (unsigned long)e->shdr[i]->sh_offset);
	i++;
	while (i < e->header->e_shnum - 1)
	{
		printf("offset before %lx et la size %lx\n", (unsigned long)e->shdr[i]->sh_offset, (unsigned long)e->shdr[i - 1]->sh_size);
		e->shdr[i]->sh_offset += e->shdr[last]->sh_size + loader->sh_size;
		printf("offset after %lx\n", (unsigned long)e->shdr[i]->sh_offset);
		i++;
	}
	e->header->e_shoff += loader->sh_size + 16;
	i = 0;
	while (i < e->header->e_phnum)
	{
		printf("phdr %lx shdr %lx\n", (unsigned long)(e->phdr[i]->p_vaddr + e->phdr[i]->p_memsz), (unsigned long)(e->shdr[last]->sh_addr + e->shdr[last]->sh_size));
		if (((e->phdr[i]->p_vaddr + e->phdr[i]->p_memsz) == (e->shdr[last]->sh_addr + e->shdr[last]->sh_size)) && last != 0)
		{
			printf("ici size mem %ld size file %ld\n", (unsigned long)e->phdr[i]->p_memsz, (unsigned long)e->phdr[i]->p_filesz);
			e->phdr[i]->p_memsz += 0x40;
			e->phdr[i]->p_filesz += 0x40;
			e->phdr[i - 1]->p_flags = PF_X | PF_W | PF_R;
			memcpy(e->fwoody.content + e->header->e_phoff + (e->header->e_phentsize * (i - 1)), e->phdr[i - 1], sizeof(Elf64_Phdr));
			e->phdr[i]->p_flags = PF_X | PF_W | PF_R;
			last = 0;
			printf("ici size mem %ld size file %ld\n", (unsigned long)e->phdr[i]->p_memsz, (unsigned long)e->phdr[i]->p_filesz);
		}
		memcpy(e->fwoody.content + e->header->e_phoff + (e->header->e_phentsize * i), e->phdr[i], sizeof(Elf64_Phdr));
		printf("addr write %lx\n", e->header->e_phoff + (e->header->e_phentsize * i));
		i++;
	}

}

void			creat_new_section(t_env *e)
{
	int				fd;
	int				i;
	Elf64_Shdr		loader;

	i = 0;
	e->fwoody.size = e->file.size + e->header->e_shentsize + 16 + 64;
	if (!(e->fwoody.content = (void *)malloc(e->fwoody.size)))
		return ;
	printf("coucou\n");
	memcpy(e->fwoody.content, e->file.content, e->file.size);//e->file.size);
	e->header->e_shnum += 1;
	e->fwoody.size = e->file.size + e->header->e_shentsize + 16 + 64;
	fd = open("woody", O_CREAT | O_RDWR, 0777);
	ft_memcpy(&loader, e->shdr[30], sizeof(Elf64_Shdr));
	fill_loader_section(e, &loader);
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

