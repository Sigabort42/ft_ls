#include "includes/ft_ls.h"

void		ft_print_error(char *path)
{
        char	*str;

        str = ft_strrchr(path, '/');
        if (!str)
                ft_printf("ft_ls: %s: %s\n",  path, strerror(errno));
        else
                ft_printf("ls: %s: %s\n",  str + 1, strerror(errno));
}
