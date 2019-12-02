/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 04:33:16 by cobecque          #+#    #+#             */
/*   Updated: 2019/12/02 20:08:18 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"
#define buff_size 1

int			error_parsing(char *error)
{
	if (ft_strcmp(error, "nb arg") == 0)
		printf("Usage: ./woody_woodpacker file\n");
	else if (ft_strcmp(error, "magic macho64") == 0)
		printf("Not a macho64 file\n");
	else if (ft_strcmp(error, "Bad filetype") == 0)
		printf("Not an executable macho64 file\n");
	return (-1);
}

void		init_env(t_env *env, char *file)
{
	char	buff[buff_size];
	int		fd;
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
		env->file.content = malloc(off);
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

void		parsing_load(t_env *env)
{
	LOAD	*load;
	int		off;
	int		i;
	int		j;
	int		size;

	i = 0;
	off = sizeof(MACH_HEADER);
	printf("off = %d\n", off);
	while (i < (int)env->header->ncmds)
	{
		load = (LOAD *)(env->file.content + off);
		if (load->cmd == LC_MAIN)
		{
			env->off_main = off;
			env->entry = (ENTRY *)load;
		}
//		if (load->cmd == LC_SYMTAB)
//		{
//			env->symtab = (SYMB *)load;
//			env->symtab->symoff += sizeof(SEG) + sizeof(SECT);
//			env->symtab->stroff += sizeof(SEG) + sizeof(SECT);
//		}
		if (load->cmd == LC_SEGMENT_64)
		{
			env->segment = (SEG *)load;
			j = 0;
			if (ft_strcmp(env->segment->segname, "__TEXT") == 0)
			{
				env->off_seg = off;
				env->seg_text = (SEG *)env->segment;
//				env->seg_text->vmaddr += sizeof(SEG) + sizeof(SECT);
				while (j < (int)env->segment->nsects)
				{
					size = off + sizeof(SEG) + sizeof(SECT) * j;
					env->section = (SECT *)(env->file.content + size);
					if (ft_strcmp(env->section->sectname, "__text") == 0)
						env->sect_text = (SECT *)env->section;
//					env->section->offset += sizeof(SEG) + sizeof(SECT);
//					env->section->addr += sizeof(SEG) + sizeof(SECT);
//					printf("vmaddr %llx size %llx off %x addr %llx %llx\n", env->seg_text->vmaddr, env->seg_text->vmsize, env->section->offset, env->section->addr, env->section->size);
					j++;
				}
			}
		}
		i++;
		off += load->cmdsize;
	}
	env->last = (SEG *)env->segment;
	env->off_seg = off;
//	env->last->vmaddr = env->seg_text->vmaddr + env->seg_text->vmsize;
	printf("vmaddr %llx vmsize %llx\n", env->last->vmaddr, env->last->vmsize);
	printf("%x\n", env->off_seg);
	printf("%s\n", env->last->segname);
	printf("off main %x\n", env->off_main);
	printf("off %llx  && size %llx\n", env->last->fileoff, env->last->filesize);
}

void		write_new(t_env *env)
{
	int			change;
	uint64_t	addr;
	int			fd;
	int			size;

//	printf("vm addr %llx vm size %llx vm addr %llx vmsize %llx off %x addr %llx size %llx\n", env->last->vmaddr, env->last->vmsize, env->segment->vmaddr, env->segment->vmsize, env->section_write->offset, env->section_write->addr, env->section_write->size);
	size = env->file.size + 16;
	ft_bzero(&env->fwoody, sizeof(t_file_inf));
	if (!(fd = open("woody", O_CREAT | O_RDWR, 0777)))
		return;
	env->fwoody.content = NULL;
	if (!(env->fwoody.content = (void *)malloc(size)))
		return;
	if (size % 16 != 0)
		size += (16 - size % 16);
	env->fwoody.size = size;
	size = env->off_seg;
	memcpy(env->fwoody.content, env->file.content, size);
	
	ft_strcpy(env->seg_text->segname, "__HI");
	env->seg_text->cmd = LC_SEGMENT_64;
	env->seg_text->cmdsize = sizeof(SEG) + sizeof(SECT);
	env->seg_text->vmaddr = env->last->vmaddr + env->last->filesize;
	env->seg_text->vmsize = getpagesize();
	env->seg_text->fileoff = env->last->fileoff + env->last->filesize;
	env->seg_text->filesize = 16;
	env->seg_text->nsects = 1;
	memcpy(env->fwoody.content + size, env->seg_text, sizeof(SEG));
	size += sizeof(SEG);

	ft_strcpy(env->sect_text->sectname, "__HERE");
	ft_strcpy(env->sect_text->segname, "__HI");
	env->sect_text->addr = env->seg_text->vmaddr;
	env->sect_text->size = env->seg_text->filesize;
	env->sect_text->offset = env->seg_text->fileoff;
	memcpy(env->fwoody.content + size, env->sect_text, sizeof(SECT));
	size += sizeof(SECT);

	change = env->file.size - env->off_seg - sizeof(SECT) - sizeof(SEG);
	memcpy(env->fwoody.content + size, env->file.content + env->off_seg + sizeof(SECT) + sizeof(SEG), change);
	
	size = env->sect_text->offset;
	memcpy(env->fwoody.content + env->off_main, &env->new_entry, 4);

	printf("%d et size %d %d\n", env->fwoody.size, size + 0x05, env->fwoody.size - (size + 5) - 1);
	memset(env->fwoody.content + size, 0xe9, 1);
	addr = env->old_entry;
	memcpy(env->fwoody.content + size + 0x01, &addr, 4);
	memset(env->fwoody.content + size + 0x05, 0, env->fwoody.size - (size + 0x05) - 1);

	printf("%d && %x && %x\n", size, env->fwoody.size, env->file.size);
	write(fd, (char *)env->fwoody.content, env->fwoody.size);
	close(fd);
}

void		fill_info_env(t_env *env)
{
	printf("cmdsize %x vmaddr %llx vmsize %llx fileoff %llx filesize %llx nbsects %d\n", env->seg_text->cmdsize, env->seg_text->vmaddr, env->seg_text->vmsize, env->seg_text->fileoff, env->seg_text->filesize, env->seg_text->nsects);
	printf("addr %llx size %llx off %x\n", env->sect_text->addr, env->sect_text->size, env->sect_text->offset);
	printf("cmdsize %x vmaddr %llx vmsize %llx fileoff %llx filesize %llx nbsects %d\n", env->last->cmdsize, env->last->vmaddr, env->last->vmsize, env->last->fileoff, env->last->filesize, env->last->nsects);

	/*env->seg_text->vmaddr += sizeof(SEG) + sizeof(SECT);
	env->last->vmaddr += sizeof(SEG) + sizeof(SECT);
	env->sect_text->addr += sizeof(SEG) + sizeof(SECT);
	env->sect_text->offset += sizeof(SEG) + sizeof(SECT);

	printf("vm addr seg text %llx vm addr last %llx addr sect %llx off sect %x\n", env->seg_text->vmaddr, env->last->vmaddr, env->sect_text->addr, env->sect_text->offset);
*/
	env->off_start = env->last->fileoff + env->last->filesize;
	env->new_entry = env->last->fileoff + env->last->filesize;
	env->old_entry = env->entry->entryoff - (env->new_entry + 0x05);
	printf("old %llx new %llx calc %llx %x\n", env->entry->entryoff, env->new_entry, env->old_entry, -258);
	printf("%llx %llx\n", env->last->vmsize, env->last->filesize);
	printf("%llx puis new_entry %llx puis %llx\n", env->off_start, env->new_entry, env->old_entry);
	write_new(env);
}

//preparer la mise en memoire dans le file a off_start
//write new entry point in off_main
//then change size of text segment and text section
int			check_magic(t_env env)
{
	env.header = env.file.content;
	if (env.header->magic != MH_MAGIC_64)
		return (error_parsing("magic macho64"));
	if (env.header->filetype != MH_EXECUTE)
		return (error_parsing("Bad filetype"));
	printf("%d\n", env.header->ncmds);
	printf("%d\n", env.header->sizeofcmds);
	env.header->sizeofcmds += sizeof(SEG) + sizeof(SECT);
	env.header->ncmds += 1;
	parsing_load(&env);
	fill_info_env(&env);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	env;

	if (ac != 2)
		return (error_parsing("nb arg"));
	init_env(&env, av[1]);
	check_magic(env);

	return (0);
}
