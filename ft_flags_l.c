#include "includes/ft_ls.h"

void     ft_flags_a(t_liste *tmp)
{
	if (!tmp)
		exit(EXIT_FAILURE);
	ft_printf("%s\n", tmp->path_name);
}

void     ft_flags_l(t_liste *tmp, int a)
{
	if (!tmp)
		exit(EXIT_FAILURE);
	if (!a)
	{
		if (tmp->path_name[0] != '.')
			ft_printf("%s%5u %s%7s%7ld %.12s ",
			tmp->law, tmp->size_lnk, tmp->name_root, tmp->group,
			tmp->size, &tmp->date[4]);
	}
	else
	{
		ft_printf("%s%5u %s%7s%7li %.12s ",
		tmp->law, tmp->size_lnk, tmp->name_root, tmp->group,
	 	tmp->size, &tmp->date[4]);
	}
}
