/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:34:10 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/05 13:27:43 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	ft_stock(struct dirent *readir, char *path)
{
	int	i;

	i = ft_strlen(path) - 1;
	while (i >= 0 && path[i] != '/')
		i--;
	ft_strcpy(readir->d_name, &path[++i]);
}

void		ft_print_file(t_env *env, struct dirent *readir, char *path)
{
	if ((lstat(path, &env->s)) == -1)
	{
		ft_print_error(path);
		return ;
	}
	readir = (struct dirent *)malloc(sizeof(struct dirent));
	ft_stock(readir, path);
	env->pass = getpwuid(env->s.st_uid);
	env->grp = getgrgid(env->s.st_gid);
	env->path_file = ft_strdup(path);
	env->lst_first = ft_listenew(env, readir);
	env->lst_last = env->lst_first;
	ft_affiche(env, 0, path);
	ft_free_node(&env->lst_first);
	free(readir);
	free(env->path_file);
}
