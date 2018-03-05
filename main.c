/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:15:49 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/05 18:28:51 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void		ft_tri_liste(t_list **lst, t_env *env, int tri)
{
	if (env->flags & (1 << 4) && tri)
		ft_tri_liste_t(lst);
	else
		ft_tri_liste_ascii(lst);
}

static void		ft_tri_params2(char **avt, t_list *lst, int *i, t_env *env)
{
	t_list		*tmp;

	tmp = lst;
	if (env->flags & (1 << 3))
	{
		*i = *i + ft_lstcount(lst);
		avt[*i] = 0;
		while (tmp)
		{
			*i = *i - 1;
			avt[*i] = ft_strdup(tmp->content);
			tmp = tmp->next;
		}
		*i = ft_lstcount(lst);
		return ;
	}
	while (tmp)
	{
		avt[*i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		*i = *i + 1;
	}
	avt[*i] = 0;
}

static char		**ft_tri_params(char **av, int *i, t_env *env)
{
	t_list		*lst_file;
	t_list		*lst_dir;
	char		**avt;
	DIR			*dr;

	*i = 0;
	lst_file = 0;
	lst_dir = 0;
	while (av[*i])
	{
		if (!(dr = opendir(av[*i])))
			ft_lstpushback(&lst_file, ft_lstnew(av[*i], 1));
		else if (dr && !closedir(dr))
			ft_lstpushback(&lst_dir, ft_lstnew(av[*i], 1));
		*i = *i + 1;
	}
	(lst_file) ? ft_tri_liste(&lst_file, env, 0) : 0;
	(lst_dir) ? ft_tri_liste(&lst_dir, env, 1) : 0;
	(!(avt = (char **)malloc(sizeof(char*) * (*i + 1)))) ? exit(1) : 0;
	*i = 0;
	ft_tri_params2(avt, lst_file, i, env);
	ft_tri_params2(avt, lst_dir, i, env);
	env->i_file = ft_lstcount(lst_dir);
	ft_free_lst_libft(lst_file, lst_dir);
	return (avt);
}

int				main(int argc, char **argv)
{
	t_env		env;
	int			i;
	char		**avt;

	env.flags = 0;
	env.lst_first = 0;
	i = ft_parse(argv, &env, argc);
	if (i == 0 || !argv[i])
	{
		env.path = ft_strdup(".");
		ft_open_path(&env, ".", 0);
		free(env.path);
	}
	else
	{
		avt = ft_tri_params(&argv[i], &i, &env);
		ft_exec(&env, avt);
	}
	return (0);
}
