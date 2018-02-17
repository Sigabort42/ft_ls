/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:15:49 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/16 18:15:08 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int				main(int argc, char **argv)
{
	t_env	env;
	int		i;

	if (ioctl(0, TIOCGWINSZ, &env.ws) == -1)
		perror("ioctl");
	else
	{
		printf("ouloulou=>>>%d %d %d %d\n", env.ws.ws_row, env.ws.ws_col, env.ws.ws_xpixel, env.ws.ws_ypixel);
		printf("%-16s %-16s %-16s %-16s\n", "flags_l.c", "flags_l.c", "flags_l.c", "flags_l.c");
	}
	env.flags = 0;
	env.lst_first = 0;
	if (argc < 1)
		return (0);
	ft_strcpy(env.flags_stock, "adfgGlrRtui");
	i = ft_parse(argv, &env);
	if (i == 0 || !argv[i])
	{
		env.path = ft_strdup(".");
		ft_open_path(&env, ".", 0);
		free(env.path);
	}
	else
	{
		while (argv[i])
		{
			env.path = ft_strdup(argv[i]);
			ft_open_path(&env, argv[i++], 0);
			free(env.path);
		}
	}
	ft_printf("fin : %b %d %s\n", env.flags, i, argv[i]);
	while (42);
}
