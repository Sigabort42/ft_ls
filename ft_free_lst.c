/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:40:41 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/04 19:32:24 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void			ft_free_node(t_liste **node)
{
	if (!(*node))
		return ;
	free((*node)->name_root);
	free((*node)->group);
	free((*node)->path_name);
	free((*node)->date);
	if ((*node)->law[0] == 'l')
		free((*node)->path_name_link);
	free((*node)->law);
	(*node)->prev = 0;
	(*node)->next = 0;
	free(*node);
	*node = 0;
}

void			ft_free_lst2(t_liste *tmp)
{
	free(tmp->name_root);
	free(tmp->group);
	free(tmp->path_name);
	free(tmp->date);
	(tmp->law[0] == 'l') ? free(tmp->path_name_link) : 0;
	free(tmp->law);
	(tmp->next) ? tmp->next->prev = 0 : 0;
	free(tmp);
	tmp = 0;
}

void			ft_free_lst(t_env *env)
{
	t_liste		*tmp;

	if (!env->lst_first)
		return ;
	tmp = (env->flags & (1 << 2)) ? env->lst_first : env->lst_last;
	while (tmp->prev)
	{
		free(tmp->name_root);
		free(tmp->group);
		free(tmp->path_name);
		free(tmp->date);
		if (tmp->law[0] == 'l')
			free(tmp->path_name_link);
		free(tmp->law);
		(tmp->next) ? tmp->next->prev = 0 : 0;
		tmp = tmp->prev;
		free(tmp->next);
		tmp->next = 0;
	}
	ft_free_lst2(tmp);
	if (!(env->flags & (1 << 2)))
	{
		env->lst_first = 0;
		env->lst_last = 0;
	}
}
