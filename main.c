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

t_path *find_paths(t_lemin *l)
{
	t_path *paths;
	paths = NULL;
	while (bfs(l))
	{
		t_conn *path = find_path(l);
//		print_connections(path);
		t_path *new = ft_memalloc(sizeof(t_path));
		new->path = path;
		new->next = paths;
		paths = new;
		reset_graph(l->rooms);
		remove_path(l, path);
		print_rooms(l);
	}
	if (!paths)
		ft_panic(NOPATH);
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
	print_rooms(&l);
	validation(&l);
	t_path *all_paths = find_paths(&l);
	t_ants *ants = ant_farm(all_paths);
	return (0);
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
