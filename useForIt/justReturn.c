/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   justReturn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:38:33 by cobecque          #+#    #+#             */
/*   Updated: 2019/10/14 16:11:37 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int			printlol(void)
{
	printf("mdrlolyolodrole\n");
	return (1);
}

int			main(void)
{
	int		a;

	printf("testing\n");
	a = printlol();
	printf("lol\n");
	return (0);
}
