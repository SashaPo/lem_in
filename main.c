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
	ft_printf("%d\n", l->ants);
	while (l->line && get_next_line(0, &l->line) > 0)
	{
		if (ft_strlen(l->line) == 0)
			exit(1);
		if (l->line[1] == '-')
			get_links(l);
		if (l->line[0] == '#' && l->line[1] != '#')
			ft_printf("%s\n", l->line);
		//get_comments(l);
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
	int i;

	i = 0;
	while (l->line[i] != '\0')
	{
		if (l->line[i] < 48 || l->line[i] > 57)
			this_is_error();
		i++;
	}
	l->ants = ft_atoi(l->line);
}

void	ft_create_rooms(t_rooms **rooms)
{
	t_rooms *new;

	new = malloc(sizeof(t_rooms));
	new->name = NULL;
	new->next = *rooms;
	*rooms = new;
}

void	find_start_or_end(t_lemin *l)
{
	if (ft_strcmp(l->line, "##start") == 0)
	{
		get_next_line(0, &l->line);
		if (ft_strlen(l->start) != 0)
			this_is_error();
		if (ft_strcmp(l->line, "##start") == 0)
		{
			get_next_line(0, &l->line);
			l->start = l->line;
		}
		else
			l->start = l->line;
		ft_printf("start: %s\n", l->start);
	}
	if (ft_strcmp(l->line, "##end") == 0)
	{
		get_next_line(0, &l->line);
		if (ft_strlen(l->end) != 0)
			this_is_error();
		if (ft_strcmp(l->line, "##end") == 0)
		{
			get_next_line(0, &l->line);
			l->end = l->line;
		}
		else
			l->end = l->line;
		ft_printf("end: %s\n", l->end);
	}
}

void	get_rooms(t_lemin *l)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strcmp(l->line, "##start") == 0 || ft_strcmp(l->line, "##end") == 0)
		find_start_or_end(l);
	if (l->line)
	{
		ft_create_rooms(&l->rooms);
		ft_printf("line: %s, i : %d\n", l->line, i);
		int len = ft_strchr(l->line, ' ') - l->line;
		l->rooms->name = ft_strnew(len);

		ft_strncpy(l->rooms->name, l->line, len);
		ft_printf("line + 1: %s\n", l->line + 1);
		l->rooms->x = ft_atoi(ft_strchr(l->line + 1, ' '));
		// ft_printf("room x: %d\n", l->rooms->x);
		l->rooms->y = ft_atoi(ft_strchr(l->line + len + 2, ' '));
		// ft_printf("room y: %d\n", l->rooms->y);
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
