/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 17:47:52 by opokusyn          #+#    #+#             */
/*   Updated: 2018/05/11 17:48:03 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lem_in.h"

void	this_is_error(void)
{
	write(1, "ERROR\n", 6);
	exit(1);
}

int		main(int ac, char **av)
{
	static t_lemin	l;
	int comments;

    l.fd = av[1] ? open(av[1], O_RDONLY) : 0;
	comments = 0;
	if (!(get_next_line(l.fd, &l.line)))
		this_is_error();
	get_ants(&l);
	ft_printf("%d\n", l.ants);
	while (l.line && get_next_line(l.fd, &l.line) > 0)
	{
		if (ft_strlen(l.line) == 0)
			exit(1);
		if (ft_strchr(l.line, '-'))
			get_links(&l);
		else if (l.line[0] == '#' && l.line[1] != '#')
			comments++;
		else
			get_rooms(&l);
	}
	print_rooms(&l);
	// if (validation(l))
		// find_path(l);
	return (0);
}

//int		validation(t_lemin *l)
//{
//	int check;
//
//	check = 0;
//	if (l.rooms->name == NULL)
//	{
//		ft_printf("no rooms!\n");
//		this_is_error();
//		return(0);
//	}
//	if (l->start == 0)
//	{
//		ft_printf("no start!\n");
//		this_is_error();
//		return(0);
//	}
//	if (l->end == 0)
//	{
//		ft_printf("no end!\n");
//		this_is_error();
//		return(0);
//	}
//	return (1);
//}




void	get_ants(t_lemin *l)
{
	int i;

	i = 0;
	while (l->line[i] != '\0')
	{
		if (l->line[i] < 48 || l->line[i] > 57)
			this_is_error();
		i++;
	}
	i = 0;
	l->ants = ft_atoi(l->line);
	if (l->ants <= 0 || l->ants > 2147483647)
		this_is_error();
}

void	ft_create_rooms(t_rooms **rooms)
{
	t_rooms *new;

	new = malloc(sizeof(t_rooms));
	new->name = NULL;
    new->connections = NULL;
	new->next = *rooms;
	*rooms = new;
}

void	find_start_or_end(t_lemin *l)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strcmp(l->line, "##start") == 0)
	{
		get_next_line(l->fd, &l->line);
		if (l->start)
			this_is_error();
		else
		{
			if (ft_strchr(l->line, '#') || ft_strchr(l->line, '-'))
			{
				l->start = 0;
				validation(l);
			}
			else
			{
                l->start = ft_strnew(ft_strchr(l->line, ' ') - l->line);
				while (l->line[i] && l->line[i] != ' ')
					l->start[j++] = l->line[i++];
			}
		}
		ft_printf("start: %s\n", l->start);
	}
	if (ft_strcmp(l->line, "##end") == 0)
	{
		get_next_line(l->fd, &l->line);
		if (l->end)
			this_is_error();
		else
		{
			if ((ft_strchr(l->line, '#') || ft_strchr(l->line, '-')))
			{
				l->end = 0;
				validation(l);
			}
			else
			{
                l->end = ft_strnew(ft_strchr(l->line, ' ') - l->line);
                while (l->line[i] && l->line[i] != ' ')
					l->end[j++] = l->line[i++];
			}
		}
		ft_printf("end: %s\n", l->end);
	}
}

int		check_spaces(t_lemin *l)
{
	int		i;
	int		spaces;

	i = 0;
	spaces = 0;
	while(l->line[i])
	{
		if (l->line[i] == ' ')
			spaces++;
		i++;
	}
	if (spaces != 2)
		return(1);
	return(0);
}

int		check_str(t_lemin *l)
{
	int		i;
	int		n;

	i = 0;
	n = 65;
	while (n < 122)
	{
		if (ft_strchr(l->line + 1, n++))
		{
			ft_printf("not a valid line!!!!\n");
			this_is_error();
		}
	}
	return (0);
}

void	get_rooms(t_lemin *l)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strcmp(l->line, "##start") == 0 || ft_strcmp(l->line, "##end") == 0)
		find_start_or_end(l);
	if (check_spaces(l))
		l->line = NULL;
	if (l->line)
	{
		ft_create_rooms(&l->rooms);
		int len = ft_strchr(l->line, ' ') - l->line;
		l->rooms->name = ft_strnew(len);

		ft_strncpy(l->rooms->name, l->line, len);
		ft_printf("%s ", l->rooms->name);
		check_str(l);
		l->rooms->x = ft_atoi(ft_strchr(l->line + 1, ' '));
		if (l->rooms->x < 0 || l->rooms->x > 2147483647)
		{
			ft_printf("not integer!!!!\n");
			this_is_error();
		}
		ft_printf("%d ", l->rooms->x);
		l->rooms->y = ft_atoi(ft_strchr(l->line + len + 2, ' '));
		if (l->rooms->y < 0 || l->rooms->y > 2147483647)
		{
			ft_printf("not integer!!!!\n");
			this_is_error();
		}
		ft_printf("%d\n", l->rooms->y);
	}
}

void	ft_create_links(t_links **links)
{
	t_links *new;

	new = malloc(sizeof(t_links));
	new->name1 = malloc(sizeof(t_links));
	new->name2 = malloc(sizeof(t_links));
	new->next = *links;
	*links = new;
}

t_rooms *find_room(t_lemin *l, char *name)
{
	t_rooms *copy;

	copy = l->rooms;
	while (copy)
	{
		if (ft_strcmp(copy->name, name) == 0)
		{
			return (copy);
			break ;
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

void	print_rooms(t_lemin *l)
{
	t_rooms *copy;
	t_conn *conn_iter;

	copy = l->rooms;
	while(copy)
	{
		ft_printf("room name: %s [", copy->name);
		conn_iter = copy->connections;
		while (conn_iter)
		{
			ft_printf("%s ", conn_iter->room->name);
			conn_iter = conn_iter->next;
		}
		ft_printf("]\n");
		copy = copy->next;
	}
}

void	get_links(t_lemin *l)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (l->line)
	{
		ft_create_links(&l->links);
		while (l->line[i] != '-')
			l->links->name1[j++] = l->line[i++];
		j = 0;
		i = i + 1;
		while (l->line[i] != '\0')
			l->links->name2[j++] = l->line[i++];
		ft_printf("%s-%s\n", l->links->name1, l->links->name2);
		t_rooms *room1 = find_room(l, l->links->name1);
		t_rooms *room2 = find_room(l, l->links->name2);
		if (room1 && room2)
			connect_rooms(room1, room2);
		else
			ft_printf("Something wrong\n");
	}
}
