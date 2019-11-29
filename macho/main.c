/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 04:33:16 by cobecque          #+#    #+#             */
/*   Updated: 2019/11/29 11:46:45 by cobecque         ###   ########.fr       */
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
			env->off_main = off + 8;
			env->entry = (ENTRY *)load;
		}
		if (load->cmd == LC_SEGMENT_64)
		{
			env->segment = (SEG *)load;
			j = 0;
			if (ft_strcmp(env->segment->segname, "__TEXT") == 0)
			{
				env->seg_text = (SEG *)env->segment;
				while (j < (int)env->segment->nsects)
				{
					size = off + sizeof(SEG) + sizeof(SECT) * j;
					env->section = (SECT *)(env->file.content + size);
					if (ft_strcmp(env->section->sectname, "__text") == 0)
						env->sect_text = (SECT *)env->section;
					j++;
				}
			}
		}
		i++;
		off += load->cmdsize;
	}
	env->last = (SEG *)env->segment;
	printf("%s\n", env->last->segname);
	printf("off main %x\n", env->off_main);
	printf("off %llx  && size %llx\n", env->last->fileoff, env->last->filesize);
}

void		fill_info_env(t_env *env)
{
	env->off_start = env->last->fileoff + env->last->filesize;
	env->new_entry = env->last->vmaddr + env->last->vmsize;
	env->old_entry = env->entry->entryoff - env->new_entry;
	printf("%llx %llx\n", env->last->vmsize, env->last->filesize);
	printf("%llx puis new_entry %llx puis %llx\n", env->off_start, env->new_entry, env->old_entry);
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
