/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:15:49 by elbenkri          #+#    #+#             */
/*   Updated: 2018/01/25 18:15:40 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	main(int argc, char **argv)
{
	t_env	env;
	int	i;

	env.flags = 0;
	if (argc < 1)
		return (0);
	ft_strcpy(env.flags_stock, "adfgGlrRtu");
	i = ft_parse(argv, &env);
	ft_printf("%b %s\n", env.flags, argv[i]);
}






















/*
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int	main(int argc, char **argv)
{
	struct stat		s;
	struct passwd	*pass;
	struct group	*gr;
	int				ret;

	if (argc < 2)
		return (0);
	if ((stat(argv[1], &s)) == -1)
	{
		perror("stat");
		return (0);
	}
	printf("Nom : %s\n", argv[1]);
	if (S_ISREG(s.st_mode))
		printf("Type : fichier\n");
	else if (S_ISDIR(s.st_mode))
		printf("Type : repertoire\n");
	else if (S_ISCHR(s.st_mode))
		printf("Type : fichier caractere\n");
	else if (S_ISBLK(s.st_mode))
		printf("Type : fichier block\n");
	else if (S_ISLNK(s.st_mode))
		printf("Type : lien Symbolique\n");
	else if (S_ISSOCK(s.st_mode))
		printf("Type : sockets\n");
	printf("modes : ");
	printf((S_ISDIR(s.st_mode)) ? "d" : "-");
    printf((s.st_mode & S_IRUSR) ? "r" : "-");
    printf((s.st_mode & S_IWUSR) ? "w" : "-");
    printf((s.st_mode & S_IXUSR) ? "x" : "-");
    printf((s.st_mode & S_IRGRP) ? "r" : "-");
    printf((s.st_mode & S_IWGRP) ? "w" : "-");
    printf((s.st_mode & S_IXGRP) ? "x" : "-");
    printf((s.st_mode & S_IROTH) ? "r" : "-");
    printf((s.st_mode & S_IWOTH) ? "w" : "-");
    printf((s.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
	printf("Nombre de liens : %d\n", s.st_nlink);
	pass = getpwuid(s.st_uid);
	gr = getgrgid(s.st_gid);
	printf("Proprietaire : %s\n", pass->pw_name);
	printf("Groupe : %s\n", gr->gr_name);
	printf("Taille : %lld\n", s.st_size);
	char *str = ctime(&s.st_mtime);
	printf("Date de derniere modification : %.12s\n", &str[4]);
	return (0);
}
*/
