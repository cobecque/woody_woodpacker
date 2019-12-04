/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 06:43:18 by cobecque          #+#    #+#             */
/*   Updated: 2019/12/04 15:41:23 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"
#include <stdio.h>
#include <stdlib.h>
#include "sys/mman.h"

#define buff_size 1

int			fill_algo(int *algo_idx, char *algo)
{
	int			i;
	const char	*alg_name[] = {NULL, "rc4"};

	i = 0;
	if (algo[0] == '-')
	{
		if (_ft_strlen(algo) == 1)
			return(ft_error_parsing("no algo"));
		else
		{
			algo++;
			while (i < NB_ALGO)
			{
				if (ft_strcmp(alg_name[i], algo) == 0)
				{
					*algo_idx = i;
					break ;
				}
				i++;
			}
			if (i >= NB_ALGO && *algo_idx == 0)
			{
				ft_error_parsing("bad algo");
				exit (-1);
			}
		}
	}
	if (*algo_idx != 0)
		return (1);
	return (0);
}

void		pars_option_after_exec(int ac, char **av, int exc, t_parser *inf)
{
	if (exc < ac && ft_strcmp("-k", av[exc]) == 0 && _ft_strlen(av[exc]) == 2)
	{
		if (ft_strcmp(av[exc], "-k") == 0)
		{
			exc++;
			if (exc < ac)
				inf->key = av[exc];
			else
			{
				printf("%s", NO_KEY);
				exit (-1);
			}
			exc++;
		}
	}
	else if (exc < ac && inf->algo == 0 && fill_algo(&inf->algo, av[exc]) != 0)
		exc++;
	else
	{
		if (inf->algo != 0)
			printf("Invalid option or tried to use 2 or more algo\n");
		else
			printf("Invalid option:\n%s", USAGE_MSG);
		exit (-1);
	}
	if (exc < ac)
		pars_option_after_exec(ac, av, exc, inf);
}

t_parser	pars_information(int ac, char **av)
{
	int			exc;
	t_parser	inf;

	ft_bzero(&inf, sizeof(t_parser));
	exc = 1;
	if (fill_algo(&inf.algo, av[exc]) != 0)
		exc++;
	if (exc < ac)
	{
		if (ft_strcmp(av[exc], "-k") == 0)
		{
			exc++;
			if (exc < ac)
				inf.key = av[exc];
			else
			{
				printf("%s", NO_KEY);
				exit (-1);
			}
			exc++;
		}
	}
	if (exc < ac)
	{
		if (ft_strcmp("-", av[exc]) == 0 && exc < ac)
			pars_option_after_exec(ac, av, exc, &inf);
		else
		{
			inf.exec = av[exc];
			exc++;
			if (exc < ac)
				pars_option_after_exec(ac, av, exc, &inf);
		}
	}
	return (inf);
}

int			init_rc4(t_rc4 *var, t_parser inf)
{
	var->key_len = 0;
	if (!inf.key)
		var->key = random_key_gen(&var->key_len);
	else
	{
		if (check_key((unsigned char *)inf.key) == -1)
			return (-1);
		var->key = key_to_hexa((unsigned char *)inf.key, &var->key_len);
	}
	return (0);
}

void		fill_code_cave(t_env *e, int end)
{
	uint64_t	addr;
	char		buf[buff_size];
	void		*file;
	int			fd;
	int			size;

	if (!(e->fwoody.content = (void *)malloc(e->file.size)))
		return ;
	e->header->e_entry = e->new_entry;
	memcpy(e->fwoody.content, e->file.content, e->file.size);
	memcpy(e->fwoody.content, e->header, e->header->e_ehsize);
	/*if ((fd = open("decrypt_test.o", O_RDONLY)) != -1) // on peut ajouter la fonction asm au code et juste la rajouter avec un memcpy sur le pointeur de la fonction
	{
		file = malloc(lseek(fd, 0, SEEK_END));
		lseek(fd, 0, SEEK_SET);
		j = 0;
		i = 0;
		while ((j = read(fd, &buf, buff_size)) > 0)
		{
			ft_memcpy(file + i, &buf, j);
			i += j;
		}
		close(fd);
	}
	memcpy(e->fwoody.content + end, file + 0x260, 0x11e);
	addr = (0x9f4 - 0x8d4) - 0x0b;
	printf("lea addr %lx\n", (unsigned long)addr);
	memcpy(e->fwoody.content + end + 0x07, &addr, 4);

	memset(e->fwoody.content + end + 0x20, 0xe9, 1);
	addr = e->old_entry - (e->new_entry + 0x05 + 0x20);
	memcpy(e->fwoody.content + end + 0x21, &addr, 4);

	addr = 0x0feb;
	memcpy(e->fwoody.content + end + 0x11e, &addr, 2);
	memset(e->fwoody.content + end + 0x11e + 0x02, 0x2e, 4);
	memset(e->fwoody.content + end + 0x11e + 0x06, 0x57, 1);
	memset(e->fwoody.content + end + 0x11e + 0x07, 0x4f, 2);
	memset(e->fwoody.content + end + 0x11e + 0x09, 0x44, 1);
	memset(e->fwoody.content + end + 0x11e + 0x0a, 0x59, 1);
	memset(e->fwoody.content + end + 0x11e + 0x0b, 0x2e, 4);
	memset(e->fwoody.content + end + 0x11e + 0x0f, 0x0a, 1);
	memset(e->fwoody.content + end + 0x11e + 0x10, 0x00, 1);

	printf("%s", (char *)(e->fwoody.content + end + 0x0b + 0x115));
	memset(e->fwoody.content + end + 0x11e + 0x10, 0xe9, 1);
	addr = e->old_entry - (e->new_entry + 0x05 + 0x11e + 0x10);
	memcpy(e->fwoody.content + end + 0x11e + 0x11, &addr, 4);*/
	memcpy(e->fwoody.content + end, &decode_rc4, size_rc4);
	size = size_rc4 - sizeof(int) + sizeof(uint64_t) + end;
	memcpy(e->fwoody.content + size, &e->addr_encrypt, size(uint64_t));
	size = size_rc4 - sizeof(int) + end;
	memcpy(e->fwoody.content + size, &e->size_encrypt, sizeof(int));
	size = size_rc4 + end;
	memset(e->fwoody.content + size, 0xe9, 1);
	addr = e->old_entry - (e->new_entry + 0x05 + size_rc4);
	memcpy(e->fwoody.content + size + 0x01, &addr, 4);
}

void		creat_new_file(t_env *e, t_rc4 var)
{
	int			fd;

	printf("%d\n", var.key_len);
	fd = open("woody", O_CREAT | O_RDWR, 0777);
	e->fwoody = encrypt_woody(e, var);
	write(fd, (char *)e->fwoody.content, e->file.size);
	close(fd);
}

//gestion double algo no file a faire

int			main(int ac, char **av)
{
	t_env		e;
	t_rc4		var;
	t_parser	inf;
	int			size;
	int			end;

	if (ac <= 1 || ac > 5)
		return (ft_error_parsing("usage error"));
	inf = pars_information(ac, av);
	if (inf.algo == 0)
		inf.algo = 1;
	if (init_rc4(&var, inf) == -1)
		return (0);
	if (!inf.exec)
		return (ft_error_parsing("no exec"));
	init_env(&e, inf.exec);
	if (e.file.content != NULL)
	{
		end = 0;
		size = 0;
		e.header = e.file.content;
		if (check_error_header(e, inf.exec) == -1)
			return (-1);
		e.old_entry = e.header->e_entry;
		e.new_entry = find_gap(e, &size, &end);
		if (size > size_rc4)
			fill_code_cave(&e, end);
		else
			creat_new_section(&e);
		creat_new_file(&e, var);
	}
	return (0);
}

