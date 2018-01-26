#ifndef FT_LS_H
# define FT_LS_H
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "./../libft/libft.h"
# include <stdio.h>

typedef struct		s_env
{
	struct stat	s;
	struct passwd	*pass;
	struct group	grp;
	char		flags_stock[9];
	short		flags;
}			t_env;

void	ft_parse(char **av, t_env *env);


#endif
