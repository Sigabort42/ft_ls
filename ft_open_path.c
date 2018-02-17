/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:03:34 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/16 17:09:54 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void			ft_stock(struct dirent *readir, char *path)
{
	int				i;

	i = ft_strlen(path) - 1;
	while (i >= 0  && path[i] != '/')
		i--;
	ft_strcpy(readir->d_name, &path[++i]);
}

void			ft_print_file(t_env *env, struct dirent *readir, char *path)
{
	if ((lstat(path, &env->s)) == -1)
	{
		perror("stat");
		return ;
	}
	readir = (struct dirent *)malloc(sizeof(struct dirent));
	ft_stock(readir, path);
	env->pass = getpwuid(env->s.st_uid);
	env->grp = getgrgid(env->s.st_gid);
	env->lst_first = ft_listenew(env, readir);
	ft_affiche(env, 0);
	free(readir);
}

static void			ft_print2(int *i, int *j, char *tmp)
{
	*i = *i + 3;
	while (*j > 0 && tmp[*j] != '/')
		*j = *j - 1;
}

static char			*ft_print(char *path, int i)
{
	char			tmp[1000];
	int				j;

	j = 0;
	if (path[0] == '.' && path[1] == '/' && (ft_strlen(path) == 2))
	{
		return (ft_strdup("."));
	}
	if (path[0] == '.')
	{
		tmp[j++] = path[i++];
		(path[1] == '/') ? tmp[j++] = path[i++] : 0;
	}
	while (path[i])
	{
		while (path[i] && path[i] != '/')
			tmp[j++] = path[i++];
		if (path[i] && path[i + 1] == '.' && path[i + 2] == '.')
			ft_print2(&i, &j, tmp);
		else if (path[i] && path[i] == '/' && tmp[j - 1] != '/')
			tmp[j++] = path[i++];
		else if (path[i] && path[i] == '/' && tmp[j - 1] == '/')
			i++;
	}
	tmp[j] = 0;
	return (ft_strdup(tmp));
}

void				ft_open_path(t_env *env, char *av, t_liste *tmp)
{
	DIR				*dr;
	struct dirent	*readir;
	char			*path_tmp;
	int				flg;

	flg = 0;
	path_tmp = "";
	if (!(dr = opendir(av)))
	{
		perror("opendir");
		ft_print_file(env, readir = NULL, av);
		return ;
	}
	while ((readir = readdir(dr)))
	{
		if ((lstat(av, &env->s)) == -1)
			perror("stat");
		if ((S_ISLNK(env->s.st_mode) && av[ft_strlen(av) - 1] != '/') ||
		env->flags & (1 << 8))
		{
			ft_strcpy(readir->d_name, av);
			env->pass = getpwuid(env->s.st_uid);
			env->grp = getgrgid(env->s.st_gid);
			env->path_file = av;
			env->lst_first = ft_listenew(env, readir);
			break;
		}
		env->path_file = ft_strjoin(av, "/");
		env->path_file = ft_strjoin_free(env->path_file, ft_strdup(readir->d_name));
		if ((lstat(env->path_file, &env->s)) == -1)
			perror("stat");
		if ((env->pass = getpwuid(env->s.st_uid)) == 0)
		{
			if (env->s.st_uid == 1000)
			{
				env->pass = (struct passwd*)malloc(sizeof(struct passwd));
				env->pass->pw_name = ft_strdup("1000");
				flg = 1;
			}
			else
			{
				flg = 0;
				continue;
			}
		}
		else
			flg = 0;
		if ((env->grp = getgrgid(env->s.st_gid)) == 0)
			continue;
		if (!(env->flags & (1 << 0)) && (!(env->flags & (1 << 6))) &&
		readir->d_name[0] == '.' && ft_strcmp(readir->d_name, "."))
			;
		else
			ft_liste_pushback(&env->lst_first, ft_listenew(env, readir));
		free(env->path_file);
		if (flg > 0)
		{
			free(env->pass->pw_name);
			free(env->pass);
		}
	}
	if (!(env->flags & (1 << 6)))
		(!(env->flags & (1 << 4))) ? ft_tri(env, 0) : ft_tri(env, 1);
	env->lst_last = ft_listelast(env->lst_first);
	(!(env->flags & (1 << 3))) ? ft_affiche(env, 0) : ft_affiche(env, 1);
	if (!(env->flags & (1 << 2)))
		ft_free_lst(env);
	closedir(dr);
	if (env->flags & (1 << 2) && env->lst_first)
	{
		while (env->lst_first)
		{
			while (env->lst_first->next && (env->lst_first->law[0] != 'd' ||
				!ft_strcmp(env->lst_first->path_name, ".") ||
				!ft_strcmp(env->lst_first->path_name, "..")))
				env->lst_first = env->lst_first->next;
			if (env->lst_first && env->lst_first->law[0] == 'd' &&
			env->lst_first->size_lnk > 2 && ft_strcmp(env->lst_first->path_name, "."))
			{
				if (ft_strstr(path_tmp, "/.."))
					free(path_tmp);
				path_tmp = ft_print(av, 0);
				ft_printf("%s/%s :\n", path_tmp, env->lst_first->path_name);
				tmp = env->lst_first;
				path_tmp = ft_strjoin_free(path_tmp, ft_strdup("/"));
				path_tmp = ft_strjoin_free(path_tmp, ft_strdup(env->lst_first->path_name));
				env->lst_first = 0;
				ft_open_path(env, path_tmp, tmp);
				env->lst_first = tmp;
			}
			if (env->lst_first)
			{
				path_tmp = ft_strjoin_free(path_tmp, ft_strdup("/.."));
				ft_free_lst(env);
				env->lst_first = env->lst_first->next;
			}
		}
		free(path_tmp);
	}
}
