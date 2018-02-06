/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:15:49 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/06 15:44:27 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	main(int argc, char **argv)
{
	t_env	env;
	int	i;

	env.flags = 0;
	env.lst_first = 0;
	if (argc < 1)
		return (0);
	ft_strcpy(env.flags_stock, "adfgGlrRtu");
	i = ft_parse(argv, &env);
	if (i == 0)
	{
		env.path = ft_strdup(".");
		ft_open_path(&env, ".", 0);
	}
	else
	{
		while (argv[i])
		{
			env.path = ft_strdup(argv[i]);
			ft_open_path(&env, argv[i++], 0);
		}
	}
	ft_printf("fin : %b %d %s\n", env.flags, i, argv[i]);
}
