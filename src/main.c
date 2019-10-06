/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 06:43:18 by cobecque          #+#    #+#             */
/*   Updated: 2019/10/06 18:48:13 by rostroh          ###   ########.fr       */
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
	if (e.file != NULL)
	{
		e.header = e.file;
		fill_program_header(&e);
		fill_section_header(&e);
		printf("OEP = 0x%lx entsize = %d\n", e.header->e_entry, e.header->e_phentsize);
	}
	return (0);
}

//printf("%d, %d, %d, %d, %d, %d, %d\n", SHN_UNDEF, SHN_LORESERVE, SHN_LOPROC, SHN_HIPROC, SHN_ABS, SHN_COMMON, SHN_HIRESERVE);
