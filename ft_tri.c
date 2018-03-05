/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tri.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:41:04 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/05 19:14:08 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	ft_tri_t2(t_env *env)
{
	t_liste	*tmp_prev;
	t_liste	*tmp_next;
	t_liste	*tmp;

	tmp = env->lst_first->next;
	while (tmp->next)
	{
		if ((tmp->timestamp_m <= tmp->next->timestamp_m) &&
		(ft_strcmp(tmp->path_name, tmp->next->path_name) > 0))
		{
			tmp_prev = tmp->prev;
			tmp_next = tmp->next;
			tmp_prev->next = tmp_next;
			tmp_next->prev = tmp_prev;
			tmp->next = tmp_next->next;
			if (tmp_next->next)
				tmp_next->next->prev = tmp;
			tmp_next->next = tmp;
			tmp->prev = tmp_next;
			tmp = env->lst_first->next;
		}
		else
			tmp = tmp->next;
	}
}

static int	ft_tri_t_split(t_env *env, t_liste **tmp_prev,
							t_liste **tmp_next, t_liste **tmp)
{
	if (*tmp && (*tmp_next)->next)
	{
		if (!(*tmp)->prev)
		{
			env->lst_first = *tmp_next;
			(*tmp)->next = (*tmp_next)->next;
			(*tmp_next)->next->prev = *tmp;
			(*tmp)->prev = *tmp_next;
			(*tmp_next)->next = *tmp;
			(*tmp_next)->prev = *tmp_prev;
			*tmp = env->lst_first;
			return (1);
		}
	}
	return (0);
}

static void	ft_tri_t(t_env *env)
{
	t_liste	*tmp_prev;
	t_liste	*tmp_next;
	t_liste	*tmp;

	tmp = env->lst_first;
	while (tmp->next)
	{
		if (tmp->timestamp_m < tmp->next->timestamp_m)
		{
			tmp_prev = tmp->prev;
			tmp_next = tmp->next;
			if (ft_tri_t_split(env, &tmp_prev, &tmp_next, &tmp))
				continue;
			tmp_prev->next = tmp_next;
			tmp_next->prev = tmp_prev;
			tmp->next = tmp_next->next;
			(tmp_next->next) ? tmp_next->next->prev = tmp : 0;
			tmp_next->next = tmp;
			tmp->prev = tmp_next;
			tmp = env->lst_first;
		}
		else
			tmp = tmp->next;
	}
	ft_tri_t2(env);
}

static void	ft_tri2(t_liste **tmp, t_env *env)
{
	t_liste	*tmp_prev;
	t_liste	*tmp_next;

	tmp_prev = (*tmp)->prev;
	tmp_next = (*tmp)->next;
	tmp_prev->next = tmp_next;
	tmp_next->prev = tmp_prev;
	(*tmp)->next = tmp_next->next;
	if (tmp_next->next)
		tmp_next->next->prev = *tmp;
	tmp_next->next = *tmp;
	(*tmp)->prev = tmp_next;
	*tmp = env->lst_first->next;
}

void		ft_tri(t_env *env, int tri)
{
	t_liste	*tmp;
	int		i;

	i = 0;
	if (((i = ft_listecount(env->lst_first)) > 1) && tri == 0)
	{
		tmp = env->lst_first->next;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->path_name, tmp->next->path_name) > 0)
				ft_tri2(&tmp, env);
			else
				tmp = tmp->next;
		}
	}
	else if (tri == 1 && i > 2)
		ft_tri_t(env);
	else if (tri == 1)
		ft_tri_t_22(env);
}
