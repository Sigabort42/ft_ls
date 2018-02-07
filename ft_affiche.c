/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affiche.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:03:45 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/06 15:40:38 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void     ft_affiche2(t_env *env)
{
	t_liste *tmp;

	tmp = env->lst_first;
	while (tmp)
	{
		if (env->flags & (1 << 1))
			ft_flags_l(tmp, env->flags & (1 << 0));
		if (env->flags & (1 << 9))
			ft_flags_g_maj(tmp, env->flags & (1 << 0), env->flags & (1 << 1));
		else if (env->flags & (1 << 0) && tmp->path_name[0] == '.')
			ft_flags_a(tmp);
		else
		{
			if ((tmp->path_name[0] != '.' && tmp->law[0] == 'l') && 
			(env->flags & (1 << 1)))
			{
				ft_putstr(tmp->path_name);
				write(1, " -> ", 4);
				ft_putstr(tmp->path_name_link);
				write(1, "\n", 1);
			}
			else if (tmp->path_name[0] != '.')
			{
				ft_putstr(tmp->path_name);
				write(1, "\n", 1);
			}
		}
		tmp = tmp->next;
	}

}

void		ft_affiche(t_env *env)
{
	t_liste *tmp;
	int     total;
 
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
	ft_affiche2(env);
	ft_putstr("\n");
}
