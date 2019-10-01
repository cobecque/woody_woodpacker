/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:21:10 by cobecque          #+#    #+#             */
/*   Updated: 2019/10/01 08:16:46 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

#include "libft.h"
#include "libftasm.h"
#ifdef __linux__
	#include <elf.h>
	typedef struct	s_env
	{
		void		*file;
		Elf64_Ehdr	*header;
		Elf64_Phdr	**phdr;
		Elf64_Shdr	**shdr;
	}				t_env;
#endif

#endif
