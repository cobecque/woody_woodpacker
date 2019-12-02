/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:21:10 by cobecque          #+#    #+#             */
/*   Updated: 2019/12/02 16:04:47 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

#include "libft.h"
#include "libftasm.h"

#define NB_ALGO 2
#define DEFAULT_KEY_SIZE 16
#define SIZE_PERM 256
#define S(x) var.perm[x]

#define ERROR_OPEN_URANDOM "Error openning urandom\n"
#define ERROR_READ_URANDOM "Error while reading urandom stream\n"
#define NO_KEY "No key specified with option -k\n"

#define KEY "key hex"
#define KEY_MSG "Key must contains hexadecimal values only\n"

#define EXEC "no exec"
#define EXEC_MSG "No exec specified\n"

#define ALGO "no algo"
#define ALGO_MSG "No algo specified\n"

#define BAD_ALGO "bad algo"
#define BAD_ALGO_MSG "Unknowned algo\n"

#define USAGE "usage error"
#define USAGE_TRUNC_1 "Usage: ./woody_woodpacker -[algo] -k [key] <executable>"
#define USAGE_TRUNC_2 "\n\nAlgo : rc4\nIf no key is provided, a random"
#define USAGE_TRUNC_3 " key will be generated\n"
#define USAGE_MSG USAGE_TRUNC_1 USAGE_TRUNC_2 USAGE_TRUNC_3

#define BAD_MAGIC ": Don't have a valid ident (magic and precision file)\n"
#define BAD_EXEC ": Not an exec file\n"
#define BAD_HEADER_SIZE ": Bad size for Elf header\n"
#define BAD_PH_OFF ": Bad offset for program header\n"
#define BAD_SH_OFF ": Bad offset for section header\n"
#define BAD_SHSTR_IND ": e_shstrndx is too far in section array\n"

typedef struct		s_parser
{
	int				algo;
	char			*key;
	char			*exec;
}					t_parser;

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
void				init_env(t_env *env, char *file);
void				fill_program_header(t_env *e);
void				fill_dynamics(t_env *e, int i);
void				fill_section_header(t_env *e);

/*
** section
*/
void				creat_new_section(t_env *env);

/*
** code_cave.c
*/
uint64_t			find_gap(t_env e, int *size_gap, int *end);

/*
** encrypt_woody.c
*/

t_file_inf			encrypt_woody(t_env *e, t_rc4 var);

/*
** ft_error.c
*/

int					ft_error_parsing(char *error);
int					check_error_header(t_env e, char *f);

#elif __APPLE__
	#include <mach-o/swap.h>
	#include <mach-o/stab.h>
	#include <mach-o/loader.h>
	#include <mach-o/ranlib.h>

	#define MACH_HEADER struct mach_header_64
	#define SECT struct section_64
	#define SEG struct segment_command_64
	#define SYMB struct symtab_command
	#define LIST struct nlist_64
	#define LOAD struct load_command
	#define ENTRY struct entry_point_command

	typedef struct	s_file_inf
	{
		int			size;
		void		*content;
	}				t_file_inf;

	typedef struct	s_env
	{
		t_file_inf	file;
		t_file_inf	fwoody;
		MACH_HEADER	*header;
		SYMB		*symtab;
		SEG			*segment;
		SEG			*segment_write;
		SECT		*section;
		SECT		*section_write;
		SEG			*seg_text;
		SECT		*sect_text;
		ENTRY		*entry;
		SEG			*last;
		int			off_main;
		int			off_seg;
		uint64_t	off_start;
		uint64_t	old_entry;
		uint64_t	new_entry;
	}				t_env;

#endif

unsigned char		*rc4(const char *plain, const void *key, int size, int len);

#endif
