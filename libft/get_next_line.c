/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 18:06:34 by opokusyn          #+#    #+#             */
/*   Updated: 2018/01/19 21:11:14 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_gnl				*ft_fd(t_gnl **buff, int fd)
{
	t_gnl			**cont;

	cont = buff;
	while (*cont)
	{
		if ((*cont)->fd == fd)
			return (*cont);
		cont = &(*cont)->next;
	}
	if (*cont == NULL)
	{
		*cont = malloc(sizeof(**cont));
		(*cont)->next = NULL;
		(*cont)->data = NULL;
		(*cont)->fd = fd;
	}
	return (*cont);
}

int					ft_reader(t_gnl *buff, char **line, char *buf)
{
	int				r;
	char			*tmp;

	if ((r = read(buff->fd, buf, BUFF_SIZE)) > 0)
	{
		buf[r] = '\0';
		tmp = ft_strjoin(buff->data ? buff->data : "", buf);
		ft_strdel(&buff->data);
		buff->data = tmp;
	}
	else
	{
		if (r >= 0 && buff->data && ft_strlen(buff->data))
		{
			*line = ft_strdup(buff->data);
			buff->data = NULL;
			return (1);
		}
		else
			return (r >= 0 ? 0 : -1);
	}
	return (2);
}

int					ft_line(t_gnl *buff, char **line)
{
	char			buf[BUFF_SIZE + 1];
	char			*break_found;
	int				llen;
	int				res;
	char			*tmp;

	while (1)
	{
		if (buff->data && (break_found = ft_strchr(buff->data, '\n')))
		{
			llen = ft_strlen(buff->data) - ft_strlen(break_found);
			*line = ft_strsub(buff->data, 0, llen);
			tmp = ft_strsub(buff->data, llen + 1, ft_strlen(buff->data) - llen);
			free(buff->data);
			buff->data = tmp;
			return (1);
		}
		else
		{
			res = ft_reader(buff, line, buf);
			if (res != 2)
				return (res);
		}
	}
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static	t_gnl	*buff;
	t_gnl			*content;
	int				res;

	res = 0;
	if (fd < 0 || !line)
		return (-1);
	content = ft_fd(&buff, fd);
	res = ft_line(content, line);
	if (res == 1)
		return (1);
	return (res);
}
