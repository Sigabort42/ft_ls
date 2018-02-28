/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:03:34 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/28 17:05:57 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int			ft_verif_open(char *av, t_env *env)
{
	DIR				*dr;
	struct dirent	*readir;

	readir = 0;
	if (!(dr = opendir(av)))
	{
		if (errno == 13)
			ft_print_error(av);
		else
			ft_print_file(env, readir, av);
		return (1);
	}
	if (ft_open_path2(env, av, dr, readir))
		return (1);
	return (0);
}

static void			ft_after_recursive(t_env *env, char **path_tmp)
{
	if (env->lst_first)
	{
		*path_tmp = ft_strjoin_free(*path_tmp, ft_strdup("/.."));
		ft_free_lst(env);
		env->lst_first = env->lst_first->next;
	}
}

static void			ft_cible_dir(t_env *env)
{
	while (env->lst_first->next && (env->lst_first->law[0] != 'd' ||
		!ft_strcmp(env->lst_first->path_name, ".") ||
		!ft_strcmp(env->lst_first->path_name, "..")))
		env->lst_first = env->lst_first->next;
}

static void			ft_traitement(char **path_tmp, char *av,
						t_env *env, int flg)
{
	if (flg == 1)
	{
		(ft_strstr(*path_tmp, "/..")) ? free(*path_tmp) : 0;
		*path_tmp = ft_print(av, 0);
		ft_printf("%s/%s :\n", *path_tmp, env->lst_first->path_name);
	}
	else
	{
		*path_tmp = ft_strjoin_free(*path_tmp, ft_strdup("/"));
		*path_tmp = ft_strjoin_free(*path_tmp,
				ft_strdup(env->lst_first->path_name));
	}
}

void				ft_open_path(t_env *env, char *av, t_liste *tmp)
{
	char			*path_tmp;

	path_tmp = "";
	if (ft_verif_open(av, env))
		return ;
	if (env->flags & (1 << 2) && env->lst_first)
	{
		while (env->lst_first)
		{
			ft_cible_dir(env);
			if (env->lst_first && env->lst_first->law[0] == 'd' &&
			env->lst_first->size_lnk >= 2 &&
			ft_strcmp(env->lst_first->path_name, ".."))
			{
				ft_traitement(&path_tmp, av, env, 1);
				tmp = env->lst_first;
				ft_traitement(&path_tmp, av, env, 0);
				env->lst_first = 0;
				ft_open_path(env, path_tmp, tmp);
				env->lst_first = tmp;
			}
			ft_after_recursive(env, &path_tmp);
		}
		free(path_tmp);
	}
}
