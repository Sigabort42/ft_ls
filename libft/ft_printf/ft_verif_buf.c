/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_buf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:24:42 by elbenkri          #+#    #+#             */
/*   Updated: 2018/01/12 03:16:36 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_verif_buf(t_var *var, const char *format)
{
	if (var->i_buf > 500)
	{
		write(1, var->buf, 500);
		var->i_buf = 0;
		ft_bzero(var->buf, 500);
	}
	var->ret += ft_stock_flags(&((char*)format)[var->ret], var);
}
