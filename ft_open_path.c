#include "includes/ft_ls.h"

static void		ft_print_file(t_env *env, struct dirent *readir, char *path)
{
	if ((stat(path, &env->s)) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	readir = (struct dirent *)malloc(sizeof(struct dirent));
	ft_strcpy(readir->d_name, path);
	env->pass = getpwuid(env->s.st_uid);
	env->grp = getgrgid(env->s.st_gid);
	env->lst_first = ft_listenew(env, readir);
	ft_printf("%s%3u %s%7s%7u %.12s %s\n",
	env->lst_first->law, env->lst_first->size_lnk, env->lst_first->name_root,
	env->lst_first->group, env->lst_first->size, &env->lst_first->date[4],
	env->lst_first->path_name);
}

static void		ft_print2(int *i, int *j, char *tmp)
{
	*i = *i + 3;
	while (*j > 0 && tmp[*j] != '/')
		*j = *j - 1;
}

static char		*ft_print(char *path, int i)
{
	char		tmp[1000];
	int		j;

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

void			ft_open_path(t_env *env, char *av, t_liste *tmp)
{
	DIR		*dr;
	struct dirent	*readir;
	char		*path;
	char		*path_tmp;

	readir = NULL;
	if (!(dr = opendir(av)))
	{
		path = av;
		ft_print_file(env, readir, path);
		return ;
	}
	while ((readir = readdir(dr)))
	{
		env->path_file = ft_strjoin(av, "/");
		env->path_file = ft_strjoin_free(env->path_file, ft_strdup(readir->d_name));
		if ((stat(env->path_file, &env->s)) == -1)
		{
			perror("stat");
			free(env->path_file);
			exit(EXIT_FAILURE);
		}
		free(env->path_file);
		env->pass = getpwuid(env->s.st_uid);
		env->grp = getgrgid(env->s.st_gid);
		ft_liste_pushback(&env->lst_first, ft_listenew(env, readir));
	}
	ft_affiche(env);
	path = av;
	if (env->flags & (1 << 2) && env->lst_first)
	{
		while (env->lst_first)
		{
			while (env->lst_first->next && (env->lst_first->law[0] != 'd' ||
				!ft_strcmp(env->lst_first->path_name, ".") ||
				!ft_strcmp(env->lst_first->path_name, "..")))
				env->lst_first = env->lst_first->next;
			if (env->lst_first && env->lst_first->law[0] == 'd' &&
			env->lst_first->size_lnk > 2)
			{
				path_tmp = ft_print(path, 0);
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
