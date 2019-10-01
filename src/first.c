/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 11:51:14 by cobecque          #+#    #+#             */
/*   Updated: 2019/10/01 06:43:01 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody_woodpacker.h"
#include <stdio.h>
#include "sys/mman.h"
#include <elf.h>

#define buff_size 1

void		ft_putstrfd_bin(int fd, char *str, size_t size)
{
	write(fd, str, size);
}

int			main(int argc, char **argv)
{
	void				*file;
	size_t				size;
	int					off;
	int					fd;
	int					i;
	Elf64_Ehdr			*header;
	Elf64_Phdr			*phdr;
	char				*buff;
	int					ret;

	buff = NULL;
	file = NULL;
	i = 0;
	ret = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	off = lseek(fd, 0, SEEK_END);
	size = off;
	file = mmap(0, off + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	off = lseek(fd, 0, SEEK_SET);
	while ((ret = read(fd, &buff, buff_size)) > 0)
	{
		printf("%d\n", ret);
		memcpy(file + i, &buff, ret);
		i += ret;
	}
	printf("%d\n", ret);
	close(fd);
	if (file != NULL)
	{
		header = file;
		printf("%d  && %d\n", header->e_phentsize, header->e_phnum);
		i = 0;
		while (i < header->e_phnum)
		{
			phdr = file + header->e_ehsize + (header->e_phentsize * i);
			printf("%d && %ld\n", phdr->p_type, phdr->p_offset);
			i++;
		}
		fd = open("woody", O_CREAT | O_WRONLY);
		ft_putstrfd_bin(fd, (char *)file, size);
		close(fd);
	}
	return (0);
}
