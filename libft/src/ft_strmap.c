/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:20:34 by cobecque          #+#    #+#             */
/*   Updated: 2019/08/18 13:20:35 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char *s, char (*f)(char))
{
	char	*new;
	char	*ptr;

	if (s)
	{
		new = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
		if (new)
		{
			ptr = new;
			while (*s != '\0')
			{
				*new = (*f)(*s);
				new++;
				s++;
			}
			*new = '\0';
			return (ptr);
		}
		return (NULL);
	}
	return (NULL);
}
