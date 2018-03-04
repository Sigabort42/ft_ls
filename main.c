/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:15:49 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/01 14:17:41 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void		ft_tri_liste2(t_list *tmp, t_list **lst)
{
	t_list		*addr;

	if (tmp && tmp->next && ft_strcmp(tmp->content, tmp->next->content) > 0)
	{
		addr = tmp->next;
		tmp->next = addr->next;
		addr->next = tmp;
		*lst = addr;
	}
}

static void		ft_tri_liste(t_list **lst)
{
	t_list		*tmp;
	t_list		*addr;

	tmp = *lst;
	while (tmp && tmp->next && tmp->next->next)
	{
		while (ft_strcmp(tmp->next->content, tmp->next->next->content) > 0)
		{
			addr = tmp->next->next;
			tmp->next->next = addr->next;
			addr->next = tmp->next;
			tmp->next = addr;
			tmp = *lst;
		}
		if (ft_strcmp(tmp->content, tmp->next->content) > 0)
		{
			addr = tmp->next;
			tmp->next = addr->next;
			addr->next = tmp;
			*lst = addr;
		}
		else
			tmp = tmp->next;
	}
	ft_tri_liste2(tmp, lst);
}

static void		ft_tri_params2(char **avt, t_list *lst, int *i)
{
	t_list		*tmp;

	tmp = lst;
	while (tmp)
	{
		avt[*i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		*i = *i + 1;
	}
	avt[*i] = 0;
}

static char		**ft_tri_params(char **av)
{
	int			i;
	t_list		*lst_file;
	t_list		*lst_dir;
	char		**avt;
	DIR			*dr;

	i = 0;
	lst_file = 0;
	lst_dir = 0;
	while (av[i])
	{
		if (!(dr = opendir(av[i])))
			ft_lstpushback(&lst_file, ft_lstnew(av[i], 1));
		else if (dr && !closedir(dr))
			ft_lstpushback(&lst_dir, ft_lstnew(av[i], 1));
		i++;
	}
	(lst_file) ? ft_tri_liste(&lst_file) : 0;
	(lst_dir) ? ft_tri_liste(&lst_dir) : 0;
	(!(avt = (char **)malloc(sizeof(char*) * (i + 1)))) ? exit(1) : 0;
	i = 0;
	ft_tri_params2(avt, lst_file, &i);
	ft_tri_params2(avt, lst_dir, &i);
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
	env.i_file = i;
	if (i == 0 || !argv[i])
	{
		env.path = ft_strdup(".");
		ft_open_path(&env, ".", 0);
		free(env.path);
	}
	else
	{
		avt = ft_tri_params(&argv[i]);
		i = 0;
		while (avt[i])
		{
			env.path = ft_strdup(avt[i]);
			ft_open_path(&env, avt[i++], 0);
			free(env.path);
			free(avt[i - 1]);
		}
	}
	while (42);
	return (0);
}
