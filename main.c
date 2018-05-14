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
#include <stdio.h>

int		main(void)
{
	t_lemin	*l;

	l = malloc(sizeof(t_lemin));
	ft_init_structure(l);
	if (!(get_next_line(0, &l->line)))
		{
			write(1, "ERROR\n", 6);
			exit(1);
		}
	get_ants(l);
	printf("%d\n", l->ants);
	while (l->line && get_next_line(0, &l->line) > 0)
	{
		// printf("%s\n", l->line);
		if (l->line[1] == '-')
			printf("%s\n", l->line);
		// get_links(l);
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
	return (*l);
}

void	get_ants(t_lemin *l)
{
	l->ants = ft_atoi(l->line);
}

void	ft_create(t_rooms **rooms)
{
	t_rooms *new;

	new = malloc(sizeof(t_rooms));
	new->next = *rooms;
	*rooms = new;
}

void	get_rooms(t_lemin *l)
{
	if (ft_strcmp(l->line, "##start") == 0)
	{
		// printf("1 %s\n", l->line);
		get_next_line(0, &l->line);
		l->start = l->line;
		printf("%s\n", l->start);
	}
	if (ft_strcmp(l->line, "##end") == 0)
	{
		get_next_line(0, &l->line);
		l->end = l->line;
		printf("%s\n", l->end);
	}
	if (l->line && l->line[1] == ' ')
	{
		ft_create(&l->rooms);
		l->rooms->name = ft_atoi(l->line);
		printf("name: %d\n", l->rooms->name);
		l->rooms->x = ft_atoi(ft_strchr(l->line + 1, ' '));
		printf("x: %d\n", l->rooms->x);
		l->rooms->y = ft_atoi(ft_strchr(l->line + 2, ' '));
		printf("y: %d\n", l->rooms->y);
	}
}