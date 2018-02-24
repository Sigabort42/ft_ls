/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:14:37 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/24 16:48:17 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstpushback(t_list **lst, t_list *elem)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
		tmp = tmp->next;
	tmp = *lst;
	if (!lst)
		return ;
	if (!(*lst))
	{
		*lst = elem;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = elem;
}
