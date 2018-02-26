#include "includes/ft_ls.h"

static void			ft_print2(int *i, int *j, char *tmp)
{
	*i = *i + 3;
	while (*j > 0 && tmp[*j] != '/')
		*j = *j - 1;
}

char				*ft_print(char *path, int i)
{
	char                    tmp[1000];
	int                             j;

	j = 0;
	if (path[0] == '.' && path[1] == '/' && (ft_strlen(path) == 2))
		return (ft_strdup("."));
	if (path[0] == '.')
	{
	 	tmp[j++] = path[i++];
		(path[1] == '/') ? tmp[j++] = path[i++] : 0;
	}
	while (path[i])
	{
		while (path[i] && path[i] != '/')
			tmp[j++] = path[i++];
		if (path[i] && path[i + 1] == '.' && path[i + 2] == '.')
			ft_print2(&i, &j, tmp);
		else if (path[i] && path[i] == '/' && tmp[j - 1] != '/')
			tmp[j++] = path[i++];
		else if (path[i] && path[i] == '/' && tmp[j - 1] == '/')
			i++;
	}
	tmp[j] = 0;
	return (ft_strdup(tmp));
}
