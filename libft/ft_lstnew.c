/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 04:26:41 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/05 17:08:57 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/stat.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*new;
	struct stat s;

	if ((new = (t_list*)malloc(sizeof(*new))) == 0)
		return (0);
	if (content == 0)
	{
		new->content = (void*)content;
		new->content_size = 0;
		new->next = 0;
		return (new);
	}
	if (lstat(content, &s) == -1)
		new->content_size = content_size;
	else
		new->content_size = s.st_mtime;
	new->content = (void*)ft_strdup((char*)content);
	new->next = 0;
	return (new);
}
