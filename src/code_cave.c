/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_cave.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:10:20 by rostroh           #+#    #+#             */
/*   Updated: 2019/10/23 14:27:52 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*
** fonction find_gap is supposed to find the unused part of text section
** fonction sans doute a revoir
*/
int			find_gap(t_env *var, int *size_gap, int *end)
{
	int			i;
	int			tr;
	int			text_end;

	i = 0;
	while (i < var->header->e_phnum)
	{
		if (var->phdr[i]->p_type == PT_LOAD && var->phdr[i]->p_flags == (PF_R | PF_X))
		{
			tr = i;
			*end = var->phdr[i]->p_offset + var->phdr[i]->p_memsz;
		}
		else if (var->phdr[i]->p_type == PT_LOAD && text_end != 0)
			*size_gap = var->phdr[i]->p_offset - *end;
		i++;
	}
	printf("size_gap = %d\n", *size_gap);
	return (tr);
}


