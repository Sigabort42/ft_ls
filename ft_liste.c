/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_liste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:04:12 by elbenkri          #+#    #+#             */
/*   Updated: 2018/02/13 17:12:17 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void		ft_law_file(mode_t st_mode, char **law)
{
	*law = (char*)malloc(11);
	if (S_ISDIR(st_mode))
		(*law)[0] = 'd';
	else if (S_ISFIFO(st_mode))
		(*law)[0] = 'p';
	else if (S_ISCHR(st_mode))
		(*law)[0] = 'c';
	else if (S_ISBLK(st_mode))
		(*law)[0] = 'b';
	else if (S_ISLNK(st_mode))
		(*law)[0] = 'l';
	else if (S_ISSOCK(st_mode))
		(*law)[0] = 's';
	else
		(*law)[0] = '-';
	(*law)[1] = (st_mode & S_IRUSR) ? 'r' : '-';
	(*law)[2] = (st_mode & S_IWUSR) ? 'w' : '-';
	(*law)[3] = (st_mode & S_IXUSR) ? 'x' : '-';
	(*law)[4] = (st_mode & S_IRGRP) ? 'r' : '-';
	(*law)[5] = (st_mode & S_IWGRP) ? 'w' : '-';
	(*law)[6] = (st_mode & S_IXGRP) ? 'x' : '-';
	(*law)[7] = (st_mode & S_IROTH) ? 'r' : '-';
	(*law)[8] = (st_mode & S_IWOTH) ? 'w' : '-';
	(*law)[9] = (st_mode & S_IXOTH) ? 'x' : '-';
	(*law)[10] = 0;
}

t_liste			*ft_listenew(t_env *env, struct dirent *dr)
{
	t_liste		*new;

	if (!(new = (t_liste*)malloc(sizeof(*new))) || !env)
		return (0);
	ft_law_file(env->s.st_mode, &new->law);
	new->name_root = ft_strdup(env->pass->pw_name);
	new->group = ft_strdup(env->grp->gr_name);
	new->size_lnk = env->s.st_nlink;
	new->size = env->s.st_size;
	new->timestamp_m = env->s.st_mtime;
	new->timestamp_a = env->s.st_atime;
	new->timestamp_c = env->s.st_ctime;
	new->date = ft_strdup(ctime(&env->s.st_mtime));
	new->date[24] = 0;
	new->path_name = ft_strdup(dr->d_name);
	if (new->law[0] == 'b' || new->law[0] == 'c')
	{
		new->major = major(env->s.st_rdev);
		new->minor = minor(env->s.st_rdev);
	}
	if (new->law[0] == 'l')
	{
		new->path_name_link = ft_strnew(50);
		readlink(env->path_file, new->path_name_link, 50);
	}
	new->next = 0;
	new->prev = 0;
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
	elem->prev = tmp;
}

t_liste			*ft_listelast(t_liste *lst)
{
	t_liste		*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
