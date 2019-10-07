/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 06:43:18 by cobecque          #+#    #+#             */
/*   Updated: 2019/10/07 15:54:51 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"
#include <stdio.h>
#include <stdlib.h>
#include "sys/mman.h"

int			main(int ac, char **av)
{
	t_env		e;

	if (ac != 2)
		return (0);
	init_env(&e, av[1]);
	if (e.file.content != NULL)
	{
		e.header = e.file.content;
		fill_program_header(&e);
		fill_section_header(&e);
		//printf("OEP = 0x%lx entsize = %d strndx = %d, shoff = %lx\n", e.header->e_entry, e.header->e_shentsize, e.header->e_shstrndx, e.header->e_shoff);
		creat_new_section(&e);
	}
	return (0);
}

//printf("%d, %d, %d, %d, %d, %d, %d\n", SHN_UNDEF, SHN_LORESERVE, SHN_LOPROC, SHN_HIPROC, SHN_ABS, SHN_COMMON, SHN_HIRESERVE);
