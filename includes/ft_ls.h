#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "./../libft/libft.h"
# include <stdio.h>

typedef struct		s_liste
{
	char		*law;
	char		*name_root;
	char		*group;
	unsigned int	size_lnk;
	unsigned int	size;
	char		*date;
	time_t		timestamp;
	char		*path_name;
	struct s_liste	*next;
	struct s_liste	*prev;
}			t_liste;

typedef struct		s_env
{
	struct stat	s;
	struct passwd	*pass;
	struct group	*grp;
	char		flags_stock[9];
	short		flags;
	char		*path;
	char		*path_file;
	t_liste		*lst_first;
	t_liste		*lst_last;
}			t_env;

int	ft_parse(char **av, t_env *env);
void	ft_open_path(t_env *env, char *av, t_liste *tmp);
t_liste	*ft_listenew(t_env *env, struct dirent *dr);
void	ft_liste_pushback(t_liste **lst, t_liste *elem);
t_liste	*ft_liste_last(t_liste *lst);
void	ft_flags_g_maj(t_liste *tmp, int a);
void	ft_flags_l(t_liste *tmp, int a);
void	ft_flags_a(t_liste *tmp);
void	ft_affiche(t_env *env);
void	ft_tri(t_env *env, int tri);

#endif
