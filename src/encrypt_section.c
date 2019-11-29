/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypt_section.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:03:37 by rostroh           #+#    #+#             */
/*   Updated: 2019/11/29 16:37:04 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

#define SH_NUM e->header->e_shnum
#define SH_ENTSIZE e->header->e_shentsize
#define SH_OFF e->header->e_shoff
#define FWOODY e->fwoody.content

extern unsigned char *_rc4();

t_file_inf			encrypt_woody(t_env *e, t_rc4 var)
{
	int				i;
	Elf64_Shdr		scthdr;

	i = 0;
	while (i < SH_NUM)
	{
		ft_memcpy(&scthdr, FWOODY + SH_OFF + SH_ENTSIZE * i, sizeof(Elf64_Shdr));
		printf("%d: %ld \n", i, scthdr.sh_offset);
		if (scthdr.sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		{
			memcpy(FWOODY + scthdr.sh_offset, _rc4((char *)(FWOODY + scthdr.sh_offset), var.key, var.key_len, (SH_OFF + SH_ENTSIZE)), scthdr.sh_size);
		}
		i++;
	}
	return (e->fwoody);
}
