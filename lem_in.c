/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 17:00:30 by opokusyn          #+#    #+#             */
/*   Updated: 2018/05/11 17:00:32 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	pushback(t_rooms *room, t_conn **list)
{
	t_conn	*node = ft_memalloc(sizeof(t_conn));
	node->room = room;
	if (!*list)
		*list = node;
	else
	{
		t_conn *copy = *list;
		while (copy->next != NULL)
			copy = copy->next;
		copy->next = node;
	}
}

void	pushfront(t_rooms *room, t_conn **list)
{
	t_conn	*node = ft_memalloc(sizeof(t_conn));
	node->room = room;
	if (!*list)
		*list = node;
	else
	{
		node->next = *list;
		*list = node;
	}
}

t_bool		bfs(t_lemin *l)
{
	t_conn *queue;

	queue = ft_memalloc(sizeof(t_conn));
	queue->room = l->start;
	while (queue)
	{
		queue->room->visited = TRUE;
		t_conn *tmp = queue->room->connections;
		while (tmp)
		{
			if (tmp->room->visited != TRUE)
			{
				pushback(tmp->room, &queue);
				tmp->room->visited = TRUE;
				tmp->room->prev = queue->room;
			}
			if (tmp->room == l->end)
			{
				tmp->room->prev = queue->room;
				return (TRUE);
			}
			tmp = tmp->next;
		}
		tmp = queue;
		queue = queue->next; // DANGER: LEAKS AHEAD
		ft_memdel((void **) &tmp);
	}
	return (FALSE);
}

t_conn	*find_path(t_lemin *l)
{
	t_conn	*path;
	t_rooms *temp;

	path = NULL;
	temp = l->end;
	while (1)
	{
		pushfront(temp, &path);
		if (temp == l->start)
			break ;
		temp = temp->prev;
	}
	return (path);
}