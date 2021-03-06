/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lst_libft.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:41:00 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/27 17:53:20 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void		ft_free_lst_libft(t_list *lst_file, t_list *lst_dir)
{
	t_list	*tmp;

	while (lst_file)
	{
		tmp = lst_file;
		lst_file = lst_file->next;
		free(tmp->content);
		free(tmp);
	}
	while (lst_dir)
	{
		tmp = lst_dir;
		lst_dir = lst_dir->next;
		free(tmp->content);
		free(tmp);
	}
}
