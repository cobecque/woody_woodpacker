/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypt_section.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:03:37 by rostroh           #+#    #+#             */
/*   Updated: 2019/10/24 15:52:46 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

#define SH_NUM e->header->e_shnum
#define SH_ENTSIZE e->header->e_shentsize
#define SH_OFF e->header->e_shoff
#define FWOODY e->fwoody.content

t_file_inf			encrypt_woody(t_env *e)
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
			printf("Une super section dites-voir\n");
		}
		i++;
	}
	return (e->fwoody);
}
