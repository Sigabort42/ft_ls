/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:08:43 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/04 20:28:13 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	ft_pass(t_env *env, int *flg)
{
	if ((env->pass = getpwuid(env->s.st_uid)) == 0)
	{
		if (env->s.st_uid)
		{
			env->pass = (struct passwd*)malloc(sizeof(struct passwd));
			env->pass->pw_name = ft_itoa(env->s.st_uid);
			*flg = 1;
		}
		else
		{
			*flg = 0;
			return (1);
		}
	}
	else
		flg = 0;
	return (0);
}
