/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 11:51:14 by cobecque          #+#    #+#             */
/*   Updated: 2019/08/20 14:21:16 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody_woodpacker.h"
#include <stdio.h>
#include "sys/mman.h"

void		ft_putstrfd_bin(int fd, char *str, size_t size)
{
	write(fd, str, size);
}

int			main(int argc, char **argv)
{
	char	*file;
	size_t	size;
	int		off;
	int		fd;
	int		i;

	i = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	off = lseek(fd, 0, SEEK_END);
	size = off;
	file = mmap(0, off + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	off = lseek(fd, 0, SEEK_SET);
	while (read(fd, &file[i], 1) > 0)
		i++;
	close(fd);
	fd = open("woody", O_CREAT | O_WRONLY);
	ft_putstrfd_bin(fd, file, size);
	close(fd);
	return (0);
}
