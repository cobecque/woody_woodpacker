/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:49:46 by rostroh           #+#    #+#             */
/*   Updated: 2019/08/18 13:16:14 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	int		len;
	char	*str;
	char	*cpy;

	len = ft_strlen(s);
	str = ft_strnew(len + 1);
	cpy = str;
	while (len > 0)
	{
		*str = s[len - 1];
		str++;
		len--;
	}
	*str = 0;
	free((char*)s);
	return (cpy);
}
