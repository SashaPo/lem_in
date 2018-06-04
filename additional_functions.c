/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:36:02 by opokusyn          #+#    #+#             */
/*   Updated: 2018/06/04 14:37:03 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_content(t_lemin *l)
{
	t_list *copy;

	copy = l->content_list;
	while (copy)
	{
		ft_printf("%s\n", copy->content);
		copy = copy->next;
	}
	ft_printf("\n");
}

int		store_line(char *line)
{
	static t_lemin *l = NULL;

	if (!l)
		l = (t_lemin *)line;
	else
		ft_lstpush_b(&l->content_list, ft_lstnew(line, ft_strlen(line) + 1));
	return (1);
}

void	pushback(t_rooms *room, t_conn **list)
{
	t_conn	*copy;
	t_conn	*node;

	node = ft_memalloc(sizeof(t_conn));
	node->room = room;
	if (!*list)
		*list = node;
	else
	{
		copy = *list;
		while (copy->next != NULL)
			copy = copy->next;
		copy->next = node;
	}
}

void	pushfront(t_rooms *room, t_conn **list)
{
	t_conn	*node;

	node = ft_memalloc(sizeof(t_conn));
	node->room = room;
	if (!*list)
		*list = node;
	else
	{
		node->next = *list;
		*list = node;
	}
}

void	ft_create_rooms(t_rooms **rooms)
{
	t_rooms *new;

	new = malloc(sizeof(t_rooms));
	ft_bzero(new, sizeof(t_rooms));
	new->next = *rooms;
	*rooms = new;
}
