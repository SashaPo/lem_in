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

#include "lem_in.h"

void	this_is_error(void)
{
	write(1, "ERROR\n", 6);
	exit(1);
}

int		main(void)
{
	t_lemin	*l;

	l = malloc(sizeof(t_lemin));
	ft_init_structure(l);
	if (!(get_next_line(0, &l->line)))
		this_is_error();
	get_ants(l);
	while (l->line && get_next_line(0, &l->line) > 0)
	{
		ft_printf("line: %s\n", l->line);
		if (ft_strlen(l->line) == 0)
			exit(1);
		if (l->line[1] == '-')
			get_links(l);
		else
			get_rooms(l);
	}
	// if (validation(l))
		// find_path(l);
	return (0);
}

t_lemin	ft_init_structure(t_lemin *l)
{
	l->start = malloc(sizeof(char *));
	l->end = malloc(sizeof(char *));
	l->line = malloc(sizeof(char *));
	l->rooms = (t_rooms *)malloc(sizeof(t_rooms));
	l->rooms->next = NULL;
	l->comment = 0;
	return (*l);
}

void	get_ants(t_lemin *l)
{
	l->ants = ft_atoi(l->line);
}

void	ft_create_rooms(t_rooms **rooms)
{
	t_rooms *new;

	new = malloc(sizeof(t_rooms));
	new->name = (char *)malloc(sizeof(char));
	new->next = *rooms;
	*rooms = new;
}

void	find_start_or_end(t_lemin *l)
{
	if (ft_strcmp(l->line, "##start") == 0)
	{
		get_next_line(0, &l->line);
		l->start = l->line;
	}
	if (ft_strcmp(l->line, "##end") == 0)
	{
		get_next_line(0, &l->line);
		l->end = l->line;
	}
}

void	get_rooms(t_lemin *l)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (l->line[0] == '#' && l->line[1] == '#')
		find_start_or_end(l);
	if (l->line)
	{
		ft_create_rooms(&l->rooms);
		while (l->line[i] != ' ')
		{
			if (l->line[0] == 'L')
				exit(1);
			else
				l->rooms->name[j++] = l->line[i++];
		}
		l->rooms->x = ft_atoi(ft_strchr(l->line + 1, ' '));
		l->rooms->y = ft_atoi(ft_strchr(l->line + 2, ' '));
	}
}

void	ft_create_links(t_links **links)
{
	t_links *new;

	new = malloc(sizeof(t_links));
	new->next = *links;
	*links = new;
}

void	get_links(t_lemin *l)
{
	if (l->line && l->line[1] == '-')
	{
		ft_create_links(&l->links);
		l->links->name1 = ft_atoi(l->line);
		ft_printf("name1: %d", l->links->name1);
		ft_printf("-");
		l->links->name2 = ft_atoi(ft_strchr(l->line + 1, '-'));
		ft_printf("%d\n", l->links->name2);
	}
}
