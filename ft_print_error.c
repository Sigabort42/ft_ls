/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:32:37 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/27 17:34:49 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void		ft_print_error(char *path)
{
	char	*str;

	str = ft_strrchr(path, '/');
	if (!str)
		ft_printf("ft_ls: %s: %s\n", path, strerror(errno));
	else
		ft_printf("ft_ls: %s: %s\n", str + 1, strerror(errno));
}
