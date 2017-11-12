/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_opereations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavagner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 00:46:39 by mavagner          #+#    #+#             */
/*   Updated: 2017/10/02 00:46:40 by mavagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			check_fd(int fd, t_line *begin_list)
{
	while (begin_list)
	{
		if (begin_list->fd == fd)
			return (1);
		begin_list = begin_list->next;
	}
	return (0);
}

t_line		*create_elem(int fd)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line));
	if (new)
	{
		new->remain = read_line(fd);
		new->next = NULL;
		new->fd = fd;
	}
	return (new);
}

void		elem_add(int fd, t_line **begin_list)
{
	t_line	*tmp;

	tmp = *begin_list;
	if (tmp == NULL)
	{
		*begin_list = create_elem(fd);
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_elem(fd);
}
