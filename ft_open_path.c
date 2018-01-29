#include "includes/ft_ls.h"

static void	ft_print_file(t_env *env, struct dirent *readir, char *path)
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

static void	ft_flags_a(t_liste *tmp)
{
	if (!tmp)
		exit(EXIT_FAILURE);
	ft_printf("%s\n", tmp->path_name);
}

static void	ft_flags_l(t_liste *tmp, int a)
{
	if (!tmp)
		exit(EXIT_FAILURE);
	if (!a)
	{
		if (tmp->path_name[0] != '.')
			ft_printf("%s%5u %s%7s%7u %.12s ",
			tmp->law, tmp->size_lnk, tmp->name_root, tmp->group,
			tmp->size, &tmp->date[4]);
	}
	else
	{
		ft_printf("%s%5u %s%7s%7u %.12s ",
		tmp->law, tmp->size_lnk, tmp->name_root, tmp->group,
		tmp->size, &tmp->date[4]);
	}
}

static void	ft_flags_G(t_liste *tmp, int a)
{
	if (!a)
	{
		if (tmp->path_name[0] != '.')
		{
			if (tmp->law[0] == 'd')
				ft_printf("{cyan}%s{eoc}\n", tmp->path_name);
			else if (tmp->law[0] == 'l')
				ft_printf("{majenta}%s{eoc}\n", tmp->path_name);
			else if (tmp->law[0] == 'p')
				ft_printf("{red}%s{eoc}\n", tmp->path_name);
			else if (tmp->law[0] == 'c')
				ft_printf("{green}%s{eoc}\n", tmp->path_name);
			else if (tmp->law[0] == 'b')
				ft_printf("{blue}%s{eoc}\n", tmp->path_name);
			else if (tmp->law[0] == 's')
				ft_printf("{yellow}%s{eoc}\n", tmp->path_name);
			else
				ft_printf("%s\n", tmp->path_name);
		}
	}
	else
	{
		if (tmp->law[0] == 'd')
			ft_printf("{cyan}%s{eoc}\n", tmp->path_name);
		else if (tmp->law[0] == 'l')
			ft_printf("{majenta}%s{eoc}\n", tmp->path_name);
		else if (tmp->law[0] == 'p')
			ft_printf("{red}%s{eoc}\n", tmp->path_name);
		else if (tmp->law[0] == 'c')
			ft_printf("{green}%s{eoc}\n", tmp->path_name);
		else if (tmp->law[0] == 'b')
			ft_printf("{blue}%s{eoc}\n", tmp->path_name);
		else if (tmp->law[0] == 's')
			ft_printf("{yellow}%s{eoc}\n", tmp->path_name);
		else
			ft_printf("%s\n", tmp->path_name);
	}
}

static void	ft_affiche(t_env *env)
{
	t_liste *tmp;
	int	total;

	total = 0;
	if (!env->lst_first)
		exit(EXIT_FAILURE);
	if (env->flags & (1 << 1))
	{
		tmp = env->lst_first;
		while (tmp)
		{
			if (ft_strcmp(tmp->path_name, "."))
				total += tmp->size_lnk;
			tmp = tmp->next;
		}
		ft_printf("total %d \n", total);
	}
	tmp = env->lst_first;
	while (tmp)
	{
		if (env->flags & (1 << 1))
			ft_flags_l(tmp, env->flags & (1 << 0));
		if (env->flags & (1 << 9))
			ft_flags_G(tmp, env->flags & (1 << 0));
		else if (env->flags & (1 << 0) && tmp->path_name[0] == '.')
			ft_flags_a(tmp);
		else
		{
			if (tmp->path_name[0] != '.')
			{
				ft_putstr(tmp->path_name);
				write(1, "\n", 1);
			}
		}
		tmp = tmp->next;
	}
	ft_putstr("\n");
}

static char	*ft_print(char *path)
{
	char	*str;
	char	tmp[1000];
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (path[0] == '.' && path[1] == '/' && (ft_strlen(path) == 2))
	{
		str = ft_strdup(".");
		return (str);
	}
	if (path[0] == '.')
	{
		tmp[j++] = path[i++];
		if (path[1] == '/')
			tmp[j++] = path[i++];
	}
	while (path[i])
	{
		while (path[i] && path[i] != '/')
			tmp[j++] = path[i++];
		if (path[i] && path[i + 1] == '.' && path[i + 2] == '.')
		{			
			i += 3;
			while (j > 0 && tmp[j] != '/')
				j--;
		}
		else if (path[i] && path[i] == '/')
			tmp[j++] = path[i++];
	}
	tmp[j] = 0;
	str = ft_strdup(tmp);
	return (str);
}

void	ft_open_path(t_env *env, char *av, t_liste *tmp)
{
	DIR		*dr;
	struct dirent	*readir;
	char		*path;
	char		*path_tmp;

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
			if (env->lst_first && env->lst_first->law[0] == 'd' &&
			env->lst_first->size_lnk > 2)
			{
				path_tmp = ft_print(path);
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
