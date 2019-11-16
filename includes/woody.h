/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:21:10 by cobecque          #+#    #+#             */
/*   Updated: 2019/10/24 15:35:54 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

#include "libft.h"
#include "libftasm.h"

#define NB_ALGO 1
#define DEFAULT_KEY_SIZE 16
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
void				print_key(const uint8_t *key, int keysz);
uint8_t				*random_key_gen(int *keysz);

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
		uint64_t	old_entry;
		uint64_t	new_entry;
		uint64_t	end_load_off;
		uint64_t	end_load_addr;
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

/*
** code_cave.c
*/
uint64_t	find_gap(t_env e, int *size_gap, int *end);

/*
** encrypt_woody.c
*/
t_file_inf	encrypt_woody(t_env *e, t_rc4 var);

unsigned char *rc4(const char *plain, const void *key, int size, int len);

#endif


#endif
