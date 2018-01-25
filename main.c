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

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

int	main(int argc, char **argv)
{
	struct stat		s;
	struct passwd	*pass;
	int				ret;

	if (argc < 2)
		return (0);
	printf("lol|%s|\n", argv[1]);
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
	printf("Proprietaire : %s\n", pass->pw_name);
	return (0);
}
