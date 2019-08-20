/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:17:27 by cobecque          #+#    #+#             */
/*   Updated: 2019/08/20 16:19:31 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <elf.h>

int			main(void)
{
	printf("%lld\n", (unsigned long long)sizeof(ELF64_Ehdr));
	printf("___WOODY___\n");
	printf("Hello World!\n");
	return (0);
}
