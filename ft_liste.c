/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_liste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:04:12 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/06 19:17:42 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static char		*ft_law_file(mode_t st_mode, char *law)
{
	if (S_ISDIR(st_mode))
		law[0] = 'd';
	else if (S_ISFIFO(st_mode))
		law[0] = 'p';
	else if (S_ISCHR(st_mode))
		law[0] = 'c';
	else if (S_ISBLK(st_mode))
		law[0] = 'b';
	else if (S_ISLNK(st_mode))
		law[0] = 'l';
	else if (S_ISSOCK(st_mode))
		law[0] = 's';
	else
		law[0] = '-';
	law[1] = (st_mode & S_IRUSR) ? 'r' : '-';
	law[2] = (st_mode & S_IWUSR) ? 'w' : '-';
	law[3] = (st_mode & S_IXUSR) ? 'x' : '-';
	law[4] = (st_mode & S_IRGRP) ? 'r' : '-';
	law[5] = (st_mode & S_IWGRP) ? 'w' : '-';
	law[6] = (st_mode & S_IXGRP) ? 'x' : '-';
	law[7] = (st_mode & S_IROTH) ? 'r' : '-';
	law[8] = (st_mode & S_IWOTH) ? 'w' : '-';
	law[9] = (st_mode & S_IXOTH) ? 'x' : '-';
	law[10] = 0;
	return (law);
}

t_liste			*ft_listenew(t_env *env, struct dirent *dr)
{
	t_liste		*new;
	char		*law;

	law = (char*)malloc(11);
	if (!(new = (t_liste*)malloc(sizeof(*new))))
		return (0);
	if (!env)
		return (0);
	new->law = ft_law_file(env->s.st_mode, law);
	new->name_root = ft_strdup(env->pass->pw_name);
	new->group = ft_strdup(env->grp->gr_name);
	new->size_lnk = env->s.st_nlink;
	new->size = env->s.st_size;
	new->timestamp = env->s.st_mtime;
	new->date = ctime(&env->s.st_mtime);
	new->date[24] = 0;
	new->path_name = ft_strdup(dr->d_name);
	new->next = 0;
	return (new);
}

void			ft_liste_pushback(t_liste **lst, t_liste *elem)
{
	t_liste		*tmp;

	if (!lst)
		return ;
	if(!(*lst))
	{
		*lst = elem;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = elem;
}
