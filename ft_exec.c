/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 19:36:04 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/04 19:39:45 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void		ft_exec(t_env *env, char **avt)
{
	int		i;

	i = 0;
	while (avt[i])
	{
		env->path = ft_strdup(avt[i]);
		ft_open_path(env, avt[i++], 0);
		free(env->path);
		free(avt[i - 1]);
	}
}
