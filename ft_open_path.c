#include "includes/ft_ls.h"

static void	ft_affiche(t_env *env)
{
	t_liste *tmp;
	int	total;

	if (!env->lst_first)
		exit(EXIT_FAILURE);
	tmp = env->lst_first;
	while (tmp)
	{
		ft_printf("%s%5u %s%7s%7u %s %s\n", tmp->law, tmp->size_lnk, tmp->name_root, tmp->group, tmp->size, tmp->date, tmp->path_name);
		tmp = tmp->next;
	}
}

void	ft_open_path(t_env *env, char *av)
{
	DIR		*dr;
	struct dirent	*readir;
	char		*path;

	ft_putstr("\n\n");
	if (!(dr = opendir(av)))
	{
		if ((stat(path, &env->s)) == -1)
		{
			perror("stat");
			exit(EXIT_FAILURE);
		}
		ft_putstr("lol\n");
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	while ((readir = readdir(dr)))
	{
		if (ft_strcmp(env->path, "./"))
		{
			path = ft_strjoin(av, "/");
			path = ft_strjoin(path, readir->d_name);
		}
		else
			path = ft_strdup(readir->d_name);
		if ((stat(path, &env->s)) == -1)
		{
			perror("stat");
			exit(EXIT_FAILURE);
		}
		env->pass = getpwuid(env->s.st_uid);
		env->grp = getgrgid(env->s.st_gid);
		if (!env->lst_first)
			env->lst_first = ft_listenew(env, readir);
		else
			ft_liste_pushback(&env->lst_first, ft_listenew(env, readir));
	}
	ft_affiche(env);
}
