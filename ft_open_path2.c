/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_path2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:06:43 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/01 19:09:59 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int	ft_open22(char *av, t_env *env, struct dirent *readir)
{
	if ((lstat(av, &env->s)) == -1)
		ft_print_error(av);
	if ((S_ISLNK(env->s.st_mode) && av[ft_strlen(av) - 1] != '/' &&
	env->flags & (1 << 1)) || env->flags & (1 << 8))
	{
		ft_strcpy(readir->d_name, av);
		env->pass = getpwuid(env->s.st_uid);
		env->grp = getgrgid(env->s.st_gid);
		env->path_file = av;
		env->lst_first = ft_listenew(env, readir);
		return (1);
	}
	env->path_file = ft_strjoin(av, "/");
	env->path_file = ft_strjoin_free(env->path_file, ft_strdup(readir->d_name));
	return (0);
}

static int	ft_flg(t_env *env, struct dirent *readir)
{
	int	flg;

	flg = 0;
	if (ft_pass(env, &flg))
		return (1);
	if ((env->grp = getgrgid(env->s.st_gid)) == 0)
		return (1);
	if (!(env->flags & (1 << 0)) && (!(env->flags & (1 << 6))) &&
		readir->d_name[0] == '.' && ft_strcmp(readir->d_name, ".") &&
		ft_strcmp(readir->d_name, ".."))
		;
	else
		ft_liste_pushback(&env->lst_first, ft_listenew(env, readir));
	free(env->path_file);
	if (flg > 0)
	{
		free(env->pass->pw_name);
		free(env->pass);
	}
	return (0);
}

int			ft_open_path2(t_env *env, char *av, DIR *dr, struct dirent *readir)
{
	while ((readir = readdir(dr)))
	{
		if (ft_open22(av, env, readir))
			break ;
		if ((lstat(env->path_file, &env->s)) == -1)
		{
			if (errno == 13)
			{
				free(env->path_file);
				if (env->s.st_mode & S_IXGRP)
					ft_print_error(av);
				closedir(dr);
				return (1);
			}
		}
		if (ft_flg(env, readir))
			continue;
	}
	if (!(env->flags & (1 << 6)))
		(!(env->flags & (1 << 4))) ? ft_tri(env, 0) : ft_tri(env, 1);
	env->lst_last = ft_listelast(env->lst_first);
	(!(env->flags & (1 << 3))) ? ft_affiche(env, 0, av) : ft_affiche(env, 1, av);
	(!(env->flags & (1 << 2))) ? ft_free_lst(env) : 0;
	closedir(dr);
	return (0);
}
