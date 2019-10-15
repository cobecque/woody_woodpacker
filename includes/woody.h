/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:21:10 by cobecque          #+#    #+#             */
/*   Updated: 2019/10/14 20:39:52 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

#include "libft.h"
#include "libftasm.h"

#define NB_ALGO 1
#define SIZE_PERM 256
#define S(x) var.perm[x]

typedef struct	s_parser
{
	int			algo;
	char		*key;
	char		*exec;
}				t_parser;

typedef struct		s_rc4
{
	uint8_t			*key;
	int				key_len;
	unsigned char	perm[SIZE_PERM];
	unsigned char	*plain;
}					t_rc4;

int					check_key(unsigned char *key);
uint8_t				*key_to_hexa(unsigned char *entry, int *size);

#ifdef __linux__
	#include <elf.h>
	typedef struct	s_file_inf
	{
		int			size;
		void		*content;
	}				t_file_inf;;

	typedef struct	s_env
	{
		t_file_inf	file;
		t_file_inf	fwoody;
		Elf64_Ehdr	*header;
		Elf64_Phdr	**phdr;
		Elf64_Shdr	**shdr;
		Elf64_Sym	**sym;
		Elf64_Dyn	**dyn;
		char		**section_name;
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
