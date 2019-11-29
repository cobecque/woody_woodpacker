/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:32:57 by rostroh           #+#    #+#             */
/*   Updated: 2019/11/29 16:27:54 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*
** Set different verbose at 0 too mute them
*/
#define VERB 0
#if VERB == 1
# define DYN_VERB 0
# define SYM_VERB 0
# define HDR_VERB 0
# define SCT_VERB 1
#else                    //do not change that field
# define DYN_VERB 0
# define SYM_VERB 0
# define HDR_VERB 0
# define SCT_VERB 0
#endif

#define buff_size 1

void			init_env(t_env *env, char *file)
{
	int		fd;
	char	buff[buff_size];
	int		ret;
	int		i;
	int		off;

	i = 0;
	ft_bzero(env, sizeof(env));
	env->file.content = NULL;
	if ((fd = open(file, O_RDONLY)) != -1)
	{
		off = lseek(fd, 0, SEEK_END);
		env->file.size = off;
		env->file.content = malloc(off);
		off = lseek(fd, 0, SEEK_SET);
		while ((ret = read(fd, &buff, buff_size)) > 0)
		{
			ft_memcpy(env->file.content + i, &buff, ret);
			i += ret;
		}
		close(fd);
	}
	else
		printf("%s: No such file or directory\n", file);
}
