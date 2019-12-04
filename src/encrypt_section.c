/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypt_section.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:03:37 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/04 14:58:20 by cobecque         ###   ########.fr       */
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
	uint64_t		last_addr;
	int				size;

	i = 0;
	e->addr_encrypt = 0;
	e->size_encrypt = 0;
	last_addr = 0;
	size = 0;
	while (i < SH_NUM)
	{
		ft_memcpy(&scthdr, FWOODY + SH_OFF + SH_ENTSIZE * i, sizeof(Elf64_Shdr));
		if (scthdr.sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		{
			if (e->addr_encrypt == 0)
				e->addr_encrypt = scthdr.sh_offset;
			last_addr = scthdr.sh_offset;
			size = scthdr.sh_size;
		}
		i++;
	}
	e->size_encrypt = (int)(last_addr - e->addr_encrypt) + size;
	_rc4(var.key, var.key_len, (char *)(FWOODY + e->addr_encrypt), e->size_encrypt);
	return (e->fwoody);
}
