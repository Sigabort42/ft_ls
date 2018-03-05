/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tri_t_22.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:57:41 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/05 19:07:52 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	ft_tri_t_22(t_env *env)
{
	t_liste	*tmp_next;
	t_liste	*tmp;

	tmp = env->lst_first;
	if (tmp->timestamp_m < tmp->next->timestamp_m)
	{
		tmp_next = env->lst_first->next;
		tmp_next->prev = 0;
		tmp_next->next = tmp;
		tmp->prev = tmp_next;
		tmp->next = 0;
		env->lst_first = tmp_next;
		env->lst_last = tmp;
	}
}
