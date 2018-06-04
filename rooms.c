/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:22:39 by opokusyn          #+#    #+#             */
/*   Updated: 2018/06/04 13:22:43 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_check_flags(t_lemin *l)
{
	if (l->is_end)
	{
		if (l->end)
			ft_panic("TWO ENDS");
		else
		{
			l->end = l->rooms;
			l->is_end = FALSE;
		}
	}
	if (l->is_start)
	{
		if (l->start)
			ft_panic("TWO STARTS");
		else
		{
			l->start = l->rooms;
			l->is_start = FALSE;
		}
	}
}

void	add_room(t_lemin *l, char *name)
{
	size_t len;

	if (check_spaces(l))
		ft_panic("bad coords\n");
	if (l->line)
	{
		ft_create_rooms(&l->rooms);
		ft_check_flags(l);
		l->rooms->name = name;
		len = ft_strlen(name);
		if (!is_numeric(l->line + len + 1))
			ft_panic("bad coords\n");
		l->rooms->x = ft_atol(ft_strchr(l->line + len + 1, ' '));
		if (l->rooms->x < 0 || l->rooms->x > 2147483647)
			ft_panic("not integer!!!!\n");
		l->rooms->y = ft_atol(ft_strchr(l->line + len + 2, ' '));
		if (l->rooms->y < 0 || l->rooms->y > 2147483647)
			ft_panic("not integer!!!!\n");
	}
}

void	get_rooms(t_lemin *l)
{
	char *roomname;

	while (get_next_line(l->fd, &l->line) > 0 && store_line(l->line))
	{
		if (ft_strlen(l->line) == 0)
			exit(1);
		else if (ft_strequ(l->line, START))
			l->is_start = TRUE;
		else if (ft_strequ(l->line, END))
			l->is_end = TRUE;
		else if (ft_strlen(l->line) && l->line[0] == '#')
			continue ;
		else
		{
			if ((roomname = ft_substr(l->line, ' ')) &&
					!ft_strchr(l->line, '-'))
				room_check(roomname, l) ? add_room(l, roomname) :
				ft_panic("room duplication!");
			else
				return (ft_strdel(&roomname));
		}
	}
}

t_rooms	*find_room(t_lemin *l, char *name)
{
	t_rooms *copy;

	copy = l->rooms;
	while (copy)
	{
		if (ft_strcmp(copy->name, name) == 0)
		{
			return (copy);
		}
		else
			copy = copy->next;
	}
	return (copy);
}

void	connect_rooms(t_rooms *from, t_rooms *to)
{
	t_conn *confrom;
	t_conn *conto;

	confrom = ft_memalloc(sizeof(t_conn));
	conto = ft_memalloc(sizeof(t_conn));
	confrom->room = from;
	conto->room = to;
	confrom->next = to->connections;
	to->connections = confrom;
	conto->next = from->connections;
	from->connections = conto;
}
