/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tri_liste2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:55:28 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/05 17:20:45 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void		ft_tri_liste_ascii2(t_list *tmp, t_list **lst)
{
	t_list			*addr;

	if (tmp && tmp->next && ft_strcmp(tmp->content, tmp->next->content) > 0)
	{
		addr = tmp->next;
		tmp->next = addr->next;
		addr->next = tmp;
		*lst = addr;
	}
}

void			ft_tri_liste_ascii(t_list **lst)
{
	t_list			*tmp;
	t_list			*addr;

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
	ft_tri_liste_ascii2(tmp, lst);
}

static void		ft_tri_liste_t2(t_list *tmp, t_list **lst)
{
	t_list			*addr;

	if (tmp && tmp->next && tmp->content_size < tmp->next->content_size)
	{
		addr = tmp->next;
		tmp->next = addr->next;
		addr->next = tmp;
		*lst = addr;
	}
}

void			ft_tri_liste_t(t_list **lst)
{
	t_list			*tmp;
	t_list			*addr;

	tmp = *lst;
	while (tmp && tmp->next && tmp->next->next)
	{
		while (tmp->content_size < tmp->next->content_size)
		{
			addr = tmp->next->next;
			tmp->next->next = addr->next;
			addr->next = tmp->next;
			tmp->next = addr;
			tmp = *lst;
		}
		if (tmp->content_size < tmp->next->content_size)
		{
			addr = tmp->next;
			tmp->next = addr->next;
			addr->next = tmp;
			*lst = addr;
		}
		else
			tmp = tmp->next;
	}
	ft_tri_liste_t2(tmp, lst);
}
