/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:15:49 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/22 18:55:52 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void			ft_tri_liste(t_list **lst)
{
	t_list			*tmp;
	t_list			*addr;

	tmp = *lst;
	while (tmp && tmp->next)
	{
		printf("boucle no %s %s %s\n", tmp->content, tmp->next->content, (*lst)->content);
		while (ft_strcmp(tmp->content, tmp->next->content) > 0)
		{
			printf("boucle %s %s %s\n", tmp->content, tmp->next->content, (*lst)->content);
			if (tmp == *lst)
				*lst = tmp->next;
			addr = tmp->next;
			tmp->next = tmp->next->next;
			addr->next = tmp;
//			tmp = first;
		}
		tmp = tmp->next;
	}
}

char			**ft_tri_params(char **av)
{
	int			i;
	t_list		*lst_file;
	t_list		*lst_dir;
	t_list		*tmp;
	t_list		*tmp2;
	char		**avt;

	i = 0;
	lst_file = 0;
	lst_dir = 0;
	while (av[i])
	{
		if (!(opendir(av[i])))
		{
			printf("av==%s\n", av[i]);
			ft_lstpushback(&lst_file, ft_lstnew(av[i], 1));
		}
		else
			ft_lstpushback(&lst_dir, ft_lstnew(av[i], 1));
		i++;
	}
	if (lst_file)
		ft_tri_liste(&lst_file);
	if (lst_dir)
		ft_tri_liste(&lst_dir);
	tmp = lst_file;
	while (tmp)
	{
		printf("lol=%s\n", tmp->content);
		tmp = tmp->next;
	}
	if (!(avt = (char **)malloc(sizeof(char*) * (i + 1))))
		return (0);
	i = 0;
	tmp = lst_file;
	tmp2 = lst_dir;
	while (tmp)
	{
		printf("tmp==%s\n", (char*)tmp->content);
		avt[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	while (tmp2)
	{
		avt[i++] = ft_strdup(tmp2->content);
		tmp2 = tmp2->next;
	}
	avt[i] = 0;
	return (avt);
}

int				main(int argc, char **argv)
{
	t_env		env;
	int			i;
	char		**avt;

	env.flags = 0;
	env.lst_first = 0;
	if (argc < 1)
		return (0);
	ft_strcpy(env.flags_stock, "adfgGlrRtui");
	i = ft_parse(argv, &env);
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
			printf("ici=>>>|%s\n", avt[i++]);
		i = 0;
		while (avt[i])
		{
			env.path = ft_strdup(avt[i]);
			ft_open_path(&env, avt[i++], 0);
			free(env.path);
		}
	}
	ft_printf("fin : %b %d %s\n", env.flags, i, argv[i]);
	while (42);
}
