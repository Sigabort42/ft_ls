#include "includes/ft_ls.h"

void			ft_free_node(t_liste **node)
{
	if (!(*node))
		return ;
	free((*node)->name_root);
	free((*node)->group);
	free((*node)->path_name);
	free((*node)->date);
	if ((*node)->law[0] == 'l')
		free((*node)->path_name_link);
	free((*node)->law);
	(*node)->prev = 0;
	(*node)->next = 0;
	free(*node);
}

void			ft_free_lst(t_env *env)
{
	t_liste		*tmp;

	if (!env->lst_first)
		return ;
	tmp = env->lst_first;
	while (tmp->prev)
	{
		free(tmp->name_root);
		free(tmp->group);
		free(tmp->path_name);
		free(tmp->date);
		if (tmp->law[0] == 'l')
			free(tmp->path_name_link);
		free(tmp->law);
		(tmp->next) ? tmp->next->prev = 0 : 0;
		tmp = tmp->prev;
		free(tmp->next);
		tmp->next = 0;
	}
	free(tmp->name_root);
	free(tmp->group);
	free(tmp->path_name);
	free(tmp->date);
	(tmp->law[0] == 'l') ? free(tmp->path_name_link) : 0;
	free(tmp->law);
	(tmp->next) ? tmp->next->prev = 0 : 0;
	free(tmp);
	tmp = 0;
}