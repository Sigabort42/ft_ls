/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tri_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 11:46:02 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/08 16:20:13 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void			ft_tri_r(t_env *env)
{
	t_liste		*tmp;
	t_liste		*temp;

	tmp = env->lst_first;
	while (tmp)
	{
		temp = tmp->prev;
		tmp->prev = tmp->next;
		tmp->next = temp;
		if (!tmp->prev)
			env->lst_first = tmp;
		tmp = tmp->prev;		
	}
}
