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
		if (ft_strchr(l->line, '-'))
			get_links(l);
		else if (l->line[0] == '#' && l->line[1] != '#')
			ft_printf("%s\n", l->line);
		else
			get_rooms(l);
	}
	if (validation(l))
		ft_printf("valid\n");
		// find_path(l);
	return (0);
}

int		validation(t_lemin *l)
{
	int check;

	check = 0;
	if (l->rooms->name == NULL)
	{
		ft_printf("no rooms!\n");
		this_is_error();
		return(1);
	}
	if (l->start == 0)
	{
		ft_printf("no start!\n");
		this_is_error();
		return(1);
	}
	if (l->end == 0)
	{
		ft_printf("no end!\n");
		this_is_error();
		return(1);
	}
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
		get_next_line(0, &l->line);
		if (ft_strlen(l->start) != 0)
			this_is_error();
		else
		{
			ft_printf("line after start: %s\n", l->line);
			if (ft_strchr(l->line, '#') || ft_strchr(l->line, '-'))
			{
				l->start = 0;
				validation(l);
			}
			else
			{
				while (l->line[i] && l->line[i] != ' ')
					l->start[j++] = l->line[i++];
			}
		}
		ft_printf("start: %s\n", l->start);
	}
	if (ft_strcmp(l->line, "##end") == 0)
	{
		get_next_line(0, &l->line);
		if (ft_strlen(l->end) != 0)
			this_is_error();
		else
		{
			ft_printf("line after end: %s\n", l->line);
			if ((ft_strchr(l->line, '#') || ft_strchr(l->line, '-')))
			{
				l->end = 0;
				validation(l);
			}
			else
			{
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
		// ft_printf("line: %s, i : %d\n", l->line, i);
		int len = ft_strchr(l->line, ' ') - l->line;
		l->rooms->name = ft_strnew(len);

		ft_strncpy(l->rooms->name, l->line, len);
		ft_printf("room name: %s\n", l->rooms->name);
		check_str(l);
		l->rooms->x = ft_atoi(ft_strchr(l->line + 1, ' '));
		ft_printf("room x: %d\n", l->rooms->x);
		l->rooms->y = ft_atoi(ft_strchr(l->line + len + 2, ' '));
		ft_printf("room y: %d\n", l->rooms->y);
	}
}

void	ft_create_links(t_links **links)
{
	t_links *new;

	new = malloc(sizeof(t_links));
	new->name1 = 0;
	new->name2 = 0;
	new->next = *links;
	*links = new;
}

void	get_links(t_lemin *l)
{
	int		i;

	i = 0;
	if (l->line)
	{
		ft_create_links(&l->links);
		l->links->name1 = ft_atoi(l->line);
		if (l->links->name1 < 0 || l->links->name1 > 2147483647)
		{
			ft_printf("not integer!!!!\n");
			this_is_error();
		}
		ft_printf("name1: %d", l->links->name1);
		ft_printf("-");
		while (l->line[i] != '-')
			i++;
		l->links->name2 = ft_atoi(&l->line[i]);
		if (l->links->name2 < 0 || l->links->name2 > 2147483647)
		{
			ft_printf("not integer!!!!\n");
			this_is_error();
		}
		ft_printf("%d\n", l->links->name2);
	}
}
