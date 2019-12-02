/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 11:56:01 by cobecque          #+#    #+#             */
/*   Updated: 2019/11/29 18:41:56 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

int			ft_error_parsing(char *error)
{
	if (ft_strcmp(error, USAGE) == 0)
		printf("%s", USAGE_MSG);
	else if (ft_strcmp(error, ALGO) == 0)
		printf("%s", ALGO_MSG);
	else if (ft_strcmp(error, EXEC) == 0)
		printf("%s", EXEC_MSG);
	else if (ft_strcmp(error, KEY) == 0)
		printf("%s", KEY_MSG);
	else if (ft_strcmp(error, BAD_ALGO) == 0)
		printf("%s%s\n", BAD_ALGO_MSG, USAGE_MSG);
	return (-1);
}

static int			check_magic(t_env env)
{
	if (env.header->e_ident[EI_MAG0] != ELFMAG0)
		return (-1);
	if (env.header->e_ident[EI_MAG1] != ELFMAG1)
		return (-1);
	if (env.header->e_ident[EI_MAG2] != ELFMAG2)
		return (-1);
	if (env.header->e_ident[EI_MAG3] != ELFMAG3)
		return (-1);
	if (env.header->e_ident[EI_CLASS] != ELFCLASS64)
		return (-1);
	if (env.header->e_ident[EI_DATA] != ELFDATA2LSB)
		return (-1);
	if (env.header->e_ident[EI_VERSION] != EV_CURRENT)
		return (-1);
	if (env.header->e_ident[EI_OSABI] != ELFOSABI_SYSV
	&& env.header->e_ident[EI_OSABI] != ELFOSABI_LINUX)
		return (-1);
	return (0);
}

static int			check_sh_off(t_env e)
{
	Elf64_Shdr	*shdr;
	int			i;
	int			off;

	i = 0;
	if (!(shdr = (Elf64_Shdr *)malloc(sizeof(Elf64_Shdr))))
		return (-1);
	while (i < e.header->e_shnum)
	{
		off = e.header->e_shoff + e.header->e_shentsize * i;
		shdr = e.file.content + off;
		if ((shdr->sh_offset + shdr->sh_size) > (uint64_t)e.file.size)
			return (-1);
		i++;
	}
	return (0);
}

static int			check_ph_off(t_env e)
{
	Elf64_Phdr	*phdr;
	int			i;
	int			off;

	i = 0;
	if (!(phdr = malloc(sizeof(Elf64_Phdr))))
		return (-1);
	while (i < e.header->e_phnum)
	{
		off = e.header->e_phoff + e.header->e_phentsize * i;
		phdr = e.file.content + off;
		if ((phdr->p_offset + phdr->p_filesz) > (uint64_t)e.file.size)
			return (-1);
		i++;
	}
	return (0);
}

int			check_error_header(t_env e, char * file)
{
	if (check_magic(e) != 0)
		printf("%s%s", file, BAD_MAGIC);
	else if (e.header->e_type != ET_EXEC && e.header->e_type != ET_DYN)
		printf("%s%s", file, BAD_EXEC);
	else if (e.header->e_ehsize > (uint64_t)e.file.size)
		printf("%s%s", file, BAD_HEADER_SIZE);
	else if (e.header->e_phoff +\
	e.header->e_phentsize * e.header->e_phnum > (uint64_t)e.file.size)
		printf("%s%s", file, BAD_PH_OFF);
	else if (e.header->e_shoff +\
	e.header->e_shentsize * e.header->e_shnum > (uint64_t)e.file.size)
		printf("%s%s", file, BAD_SH_OFF);
	else if (e.header->e_shstrndx >= e.header->e_shnum)
		printf("%s%s", file, BAD_SHSTR_IND);
	else if (check_ph_off(e) != 0)
		return (-1);
	else if (check_sh_off(e) != 0)
		return (-1);
	else
		return (0);
	return (-1);
}
