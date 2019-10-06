/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:21:10 by cobecque          #+#    #+#             */
/*   Updated: 2019/10/06 19:35:05 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

#include "libft.h"
#include "libftasm.h"
#ifdef __linux__
	#include <elf.h>
	typedef struct	file_inf
	{
		void		*content;
		int			size;
	}				t_file_inf;

	typedef struct	s_env
	{
		t_file_inf	file;
		Elf64_Ehdr	*header;
		Elf64_Phdr	**phdr;
		Elf64_Shdr	**shdr;
		Elf64_Sym	**sym;
		Elf64_Dyn	**dyn;
	}				t_env;


/*
** fill_struct.c
*/
void		init_env(t_env *env, char *file);
void		fill_program_header(t_env *e);
void		fill_dynamics(t_env *e, int i);
void		fill_section_header(t_env *e);

/*
** section
*/
void		creat_new_section(t_env *env);
#endif


#endif
