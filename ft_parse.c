/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:04:23 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/13 15:44:28 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	ft_flags_bit(char c, t_env *env)
{
	if (c == 'a')
		env->flags |= (1 << 0);
	else if (c == 'l')
		env->flags |= (1 << 1);
	else if (c == 'R')
		env->flags |= (1 << 2);
	else if (c == 'r')
		env->flags |= (1 << 3);
	else if (c == 't')
		env->flags |= (1 << 4);
	else if (c == 'u')
		env->flags |= (1 << 5);
	else if (c == 'f')
		env->flags |= (1 << 6);
	else if (c == 'g')
		env->flags |= (1 << 7);
	else if (c == 'd')
		env->flags |= (1 << 8);
	else if (c == 'G')
		env->flags |= (1 << 9);
}

static void	ft_affiche_erreur(char c)
{
	ft_putstr("ls: illegal option -- ");
	write(1, &c, 1);
	ft_putstr("\nusage: ls [-adfgGlrRtu] [file ...]\n");
	exit(EXIT_FAILURE);
}

int			ft_parse(char **av, t_env *env)
{
	int		i;
	int		j;
	char	*c;

	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] != '-')
				return (i);
			while (av[i][j] && av[i][j] != ' ')
			{
				if (!ft_strncmp(av[i], "--", 2))
					return (i + 1);
				if (!(c = ft_strchr(env->flags_stock, av[i][++j])))
					ft_affiche_erreur(av[i][j]);
				ft_flags_bit(c[0], env);
			}
		}
		j = 0;
		i++;
	}
	return (0);
}
