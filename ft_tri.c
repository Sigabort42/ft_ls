#include "includes/ft_ls.h"

static void	ft_tri_t2(t_env *env)
{
	t_liste	*tmp_prev;
	t_liste	*tmp_next;
	t_liste	*tmp;

	tmp = env->lst_first->next;
	while (tmp->next)
	{
		if ((tmp->timestamp_m <= tmp->next->timestamp_m) &&
		(ft_strcmp(tmp->path_name, tmp->next->path_name) > 0))
		{
			tmp_prev = tmp->prev;
			tmp_next = tmp->next;
			tmp_prev->next = tmp_next;
			tmp_next->prev = tmp_prev;
			tmp->next = tmp_next->next;
			if (tmp_next->next)
				tmp_next->next->prev = tmp;
			tmp_next->next = tmp;
			tmp->prev = tmp_next;
			tmp = env->lst_first->next;
		}
		else
			tmp = tmp->next;
	}
}

static void	ft_tri_t(t_env *env)
{
	t_liste	*tmp_prev;
	t_liste	*tmp_next;
	t_liste	*tmp;

	tmp = env->lst_first;
	while (tmp->next)
	{
		if (tmp->timestamp_m < tmp->next->timestamp_m)
		{
			tmp_prev = tmp->prev;
			tmp_next = tmp->next;
			if (!tmp->prev)
			{
				env->lst_first = tmp_next;
				tmp->next = tmp_next->next;
				tmp_next->next->prev = tmp;
				tmp->prev = tmp_next;
				tmp_next->next = tmp;
				tmp_next->prev = tmp_prev;
				tmp = env->lst_first;
				continue;
			}
			tmp_prev->next = tmp_next;
			tmp_next->prev = tmp_prev;
			tmp->next = tmp_next->next;
			if (tmp_next->next)
				tmp_next->next->prev = tmp;
			tmp_next->next = tmp;
			tmp->prev = tmp_next;
			tmp = env->lst_first;
		}
		else
			tmp = tmp->next;
	}
	ft_tri_t2(env);
}

void		ft_tri(t_env *env, int tri)
{
	t_liste	*tmp_prev;
	t_liste	*tmp_next;
	t_liste	*tmp;

	if (tri == 0)
	{
		tmp = env->lst_first->next;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->path_name, tmp->next->path_name) > 0)
			{
				tmp_prev = tmp->prev;
				tmp_next = tmp->next;
				tmp_prev->next = tmp_next;
				tmp_next->prev = tmp_prev;
				tmp->next = tmp_next->next;
				if (tmp_next->next)
					tmp_next->next->prev = tmp;
				tmp_next->next = tmp;
				tmp->prev = tmp_next;
				tmp = env->lst_first->next;
			}
			else
				tmp = tmp->next;
		}
	}
	else if (tri == 1)
		ft_tri_t(env);
}
