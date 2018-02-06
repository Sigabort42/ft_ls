/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:03:34 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/06 19:58:07 by elbenkri         ###   ########.fr       */
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
	ft_affiche(env);
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
		return (ft_strdup("."));
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
	char			*path;
	char			*path_tmp;
	int				flg;

	flg = 0;
	readir = (struct dirent *)malloc(sizeof(struct dirent));
	path = ft_strnew(0);
	if (!(dr = opendir(av)))
	{
		perror("opendir");
//		ft_print_file(env, readir, av);
		return ;
	}
	while ((readir = readdir(dr)))
	{
		env->path_file = ft_strjoin(av, "/");
		env->path_file = ft_strjoin_free(env->path_file, ft_strdup(readir->d_name));
		if ((lstat(env->path_file, &env->s)) == -1)
			perror("stat");
		free(env->path_file);
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
		ft_liste_pushback(&env->lst_first, ft_listenew(env, readir));
		if (flg > 0)
		{
			free(env->pass->pw_name);
			free(env->pass);
		}
	}
	ft_affiche(env);
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
			env->lst_first->size_lnk > 2 && ft_strcmp(env->lst_first->path_name, ".."))
			{
				path_tmp = ft_print(av, 0);
				ft_printf("%s/%s :\n", path_tmp, env->lst_first->path_name);
				tmp = env->lst_first;
				path = ft_strjoin(path_tmp, "/");
				path = ft_strjoin(path, env->lst_first->path_name);
				env->lst_first = 0;
				ft_open_path(env, path, tmp);
				env->lst_first = tmp;
			}
			if (env->lst_first)
			{
				path = ft_strjoin(path, "/..");
				env->lst_first = env->lst_first->next;
			}

		}
	}
}
