/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavagner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 15:37:30 by mavagner          #+#    #+#             */
/*   Updated: 2016/12/28 13:03:23 by mavagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_content	*check_and_creat_node(int check, t_content **stock, int fd)
{
	t_content		*node;

	if (check == 1)
	{
		if (!(node = (t_content*)malloc(sizeof(t_content))))
			return (NULL);
		node->content = NULL;
		node->my_fd = fd;
		node->next = NULL;
	}
	else
	{
		node = *stock;
		while (node->my_fd != fd)
		{
			node = node->next;
			if (node == NULL)
				return (NULL);
		}
	}
	return (node);
}

static char			*sub_line(t_content **cpy, int i)
{
	char			*line;

	line = ft_strsub(CPY, 0, i);
	CPY = ft_strsub_free(CPY, i + 1, ft_strlen(CPY) - ft_strlen(line));
	IF_LINE = 1;
	return (line);
}

static char			*join_line(t_content **cpy)
{
	int				i;
	int				ret;
	char			buff[BUFF_SIZE + 1];

	ret = 1;
	if (!CPY)
		if (!(CPY = (char*)ft_memalloc(sizeof(char) * 1)))
			return (NULL);
	while (ret != 0)
	{
		if ((ret = read(MY_FD, buff, BUFF_SIZE)) < 0)
			return (NULL);
		buff[ret] = '\0';
		if (!(CPY = ft_strjoin_free(CPY, buff)))
			return (NULL);
		i = -1;
		while ((CPY)[++i])
			if ((CPY)[i] == '\n')
				return (sub_line(cpy, i));
	}
	if (i > 0)
		return (sub_line(cpy, i));
	else
		IF_LINE = 0;
	return (CPY);
}

int					get_next_line(const int fd, char **line)
{
	t_content			*node;
	static	t_content	*stock = NULL;

	if (!line)
		return (-1);
	if (!stock)
		stock = check_and_creat_node(1, NULL, fd);
	if ((node = check_and_creat_node(0, &stock, fd)) == NULL)
	{
		node = stock;
		while (node->next)
			node = node->next;
		node->next = check_and_creat_node(1, NULL, fd);
		node = node->next;
	}
	if (!(*line = join_line(&node)))
		return (-1);
	return (node->if_line);
}
