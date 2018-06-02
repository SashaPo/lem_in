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


int     store_line(char *line)
{
    static t_lemin *l = NULL;

    if (!l)
        l = (t_lemin *)line;
    else
        ft_lstpush_b(&l->content_list, ft_lstnew(line, ft_strlen(line) + 1));
    return (1);
}

int		main(int ac, char **av)
{
	static t_lemin	l;
	int comments;

    store_line((char *)&l);
    l.fd = av[1] ? open(av[1], O_RDONLY) : 0;
	comments = 0;
	if (!(get_next_line(l.fd, &l.line)))
		this_is_error();
	get_ants(&l);
//	ft_printf("%d\n", l.ants);
	while (l.line && get_next_line(l.fd, &l.line) > 0 && store_line(l.line))
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
//	print_content(&l);
//	print_rooms(&l);
	 if (validation(&l))
		 find_path(&l);
	return (0);
}

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
    if (ft_strlen(l->line) > 10)
        ft_panic(ERR_ANTSTRINGTOOLONG);
    if (ft_atol(l->line) > 2147483647)
        ft_panic(ERR_BIGANT);
    l->ants = (int)ft_atol(l->line);
    if (l->ants <= 0)
		this_is_error();
}

void	find_start_or_end(t_lemin *l)
{
	if (ft_strcmp(l->line, "##start") == 0)
	{
		l->is_start = TRUE;
		get_next_line(l->fd, &l->line);
		store_line(l->line);
		if (l->start)
			this_is_error();
		else
		{
			if (ft_strchr(l->line, '#') || ft_strchr(l->line, '-'))
			{
				l->start = 0;
				validation(l);
			}
		}
	}
	if (ft_strcmp(l->line, "##end") == 0)
	{
		l->is_end = TRUE;
		get_next_line(l->fd, &l->line);
		store_line(l->line);
		if (l->end)
			this_is_error();
		else
		{
			if ((ft_strchr(l->line, '#') || ft_strchr(l->line, '-')))
			{
				l->end = 0;
				validation(l);
			}
		}
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

void	ft_create_links(t_links **links)
{
	t_links *new;

	new = malloc(sizeof(t_links));
	new->name1 = malloc(sizeof(t_links));
	new->name2 = malloc(sizeof(t_links));
	new->next = *links;
	*links = new;
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
//		ft_printf("%s-%s\n", l->links->name1, l->links->name2);
		t_rooms *room1 = find_room(l, l->links->name1);
		t_rooms *room2 = find_room(l, l->links->name2);
		if (room1 && room2)
			connect_rooms(room1, room2);
		else
			ft_panic(ERR_BADLINKNAME);
	}
}
