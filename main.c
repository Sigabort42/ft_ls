/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:15:49 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/21 17:50:00 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static char			**ft_tri_params(char **av)
{
	int			i;
	t_list		*lst_file;
	t_list		*lst_dir;
	t_list		*tmp;
	t_list		*tmp2;
	t_list		*addr;
	char		**avt;

	i = 0;
	lst_file = 0;
	lst_dir = 0;
	while (av[i])
	{
		if (!(opendir(av[i])))
			ft_lstpushback(&lst_file, ft_lstnew(av[i], 1));
		else
			ft_lstpushback(&lst_dir, ft_lstnew(av[i], 1));
		i++;
	}
	tmp = lst_file;
	tmp2 = lst_dir;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->content, tmp->next->content) > 0)
		{
			if (lst_file == tmp)
				lst_file = tmp->next;
			addr = tmp->next;
			tmp->next = tmp->next->next;
			addr->next = tmp;
			tmp = lst_file;
		}
		tmp = tmp->next;
	}
	while (tmp2->next)
	{
		if (ft_strcmp(tmp2->content, tmp2->next->content) > 0)
		{
			if (lst_dir == tmp2)
				lst_dir = tmp2->next;
			addr = tmp2->next;
			tmp2->next = tmp2->next->next;
			addr->next = tmp2;
			tmp2 = lst_dir;
		}
		tmp2 = tmp2->next;
	}
	tmp = lst_file;
	tmp2 = lst_dir;
	while (tmp)
	{
		printf("file == %s\n", (char*)tmp->content);
		tmp = tmp->next;
	}
	while (tmp2)
	{
		printf("dir == %s|%d\n", (char*)tmp2->content, i);
		tmp2 = tmp2->next;
	}	
	avt = (char **)malloc(sizeof(char*) * i + 1);
	i = 0;
	tmp = lst_file;
	tmp2 = lst_dir;
	while (tmp)
	{
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
