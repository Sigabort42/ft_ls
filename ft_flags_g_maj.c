/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_g_maj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:04:00 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/05 19:33:55 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	ft_ok(t_liste *tmp)
{
	if (tmp->law[0] == 'd')
		ft_printf("{cyan}%s{eoc}\n", tmp->path_name);
	else if (tmp->law[0] == 'l')
		ft_printf("{magenta}%s{eoc}\n", tmp->path_name);
	else if (tmp->law[0] == 'p')
		ft_printf("{red}%s{eoc}\n", tmp->path_name);
	else if (tmp->law[0] == 'c')
		ft_printf("{green}%s{eoc}\n", tmp->path_name);
	else if (tmp->law[0] == 'b')
		ft_printf("{blue}%s{eoc}\n", tmp->path_name);
	else if (tmp->law[0] == 's')
		ft_printf("{yellow}%s{eoc}\n", tmp->path_name);
	else
		ft_printf("%s\n", tmp->path_name);
}

void		ft_flags_g_maj(t_liste *tmp, int a)
{
	if (!a)
	{
		if (tmp->path_name[0] != '.')
			ft_ok(tmp);
	}
	else
		ft_ok(tmp);
}
