/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_cave.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:10:20 by rostroh           #+#    #+#             */
/*   Updated: 2019/10/23 17:10:01 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*
** fonction find_gap is supposed to find the unused part of text section
** fonction sans doute a revoir
*/
uint64_t		find_gap(t_env var, int *size_gap, int *end)
{
	Elf64_Phdr	*phdr;
	uint64_t	tr;
	int			i;
	int			off;

	i = 0;
	tr = 0;
	phdr = malloc(sizeof(Elf64_Phdr));
	while (i < var.header->e_phnum)
	{
		off = var.header->e_phoff + var.header->e_phentsize * i;
		phdr = var.file.content + off;
		if (phdr->p_type == PT_LOAD && phdr->p_flags == (PF_R | PF_X))
		{
			tr = phdr->p_vaddr + phdr->p_memsz;
			*end = phdr->p_offset + phdr->p_filesz;
		}
		else if (phdr->p_type == PT_LOAD && *end != 0)
			*size_gap = phdr->p_offset - *end;
		i++;
	}
	printf("size_gap = %d\n", *size_gap);
	return (tr);
}

