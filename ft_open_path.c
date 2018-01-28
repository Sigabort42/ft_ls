#include "includes/ft_ls.h"

static void	ft_affiche(t_env *env)
{
	t_liste *tmp;
	int	total;

	if (!env->lst_first)
		exit(EXIT_FAILURE);
	tmp = env->lst_first;
	total = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->path_name, "."))
			total += tmp->size_lnk;
		tmp = tmp->next;
	}
	tmp = env->lst_first;
	ft_printf("total %d\n", total);
	while (tmp)
	{
		ft_printf("%s%5u %s%7s%7u %.12s %s (%s)\n",
		tmp->law, tmp->size_lnk, tmp->name_root, tmp->group, tmp->size,
		&tmp->date[4], tmp->path_name, env->path);
		tmp = tmp->next;
	}
	ft_putstr("\n");
}

void	ft_print_file(t_env *env, struct dirent *readir, char *path)
{
	ft_putstr(path);
	ft_putstr("\n");
	if ((stat(path, &env->s)) == -1)
	{
		ft_putstr("opendir\n");
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

void	ft_open_path(t_env *env, char *av, t_liste *tmp)
{
	DIR		*dr;
	struct dirent	*readir;
	char		*path;
	int		i;

	readir = NULL;
	if (!(dr = opendir(av)))
	{
		printf("opendir|%s|\n", av);
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
			ft_putstr("readir\n");
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
			if (env->lst_first && env->lst_first->law[0] == 'd')
			{
				ft_printf("%s/%s/ :\n", path, env->lst_first->path_name);
				tmp = env->lst_first;
				path = ft_strjoin(path, "/");
				path = ft_strjoin(path, env->lst_first->path_name);
				env->lst_first = 0;
				ft_open_path(env, path, tmp);
				env->lst_first = tmp;
			}
			if (env->lst_first)
			{
				i = (int)ft_strlen(path) - 1;
				while (path[i] && path[i] != '/')
					i--;
				path[i] = 0;
				env->lst_first = env->lst_first->next;
			}
		}
	}
}
