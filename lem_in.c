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

void	calculate_dist(t_lemin *l)
{
	t_conn *queue;

	queue = ft_memalloc(sizeof(t_conn));
	queue->room = l->start;
	ft_printf("%s\n", queue->room->name);
	t_conn *queue_begin = queue;
	while (queue)
	{
		queue->room->visited = TRUE;
		t_conn *tmp = queue->room->connections;
		while (tmp)
		{
			if (tmp->room->visited != TRUE)
			{
				ft_printf("wtf\n");
				pushback(tmp->room, &queue);
				tmp->room->visited = TRUE;
				tmp->room->dist = queue->room->dist + 1;
			}
			if (tmp->room == l->end)
			{
				tmp->room->dist = queue->room->dist + 1;
				return ;
			}
			tmp = tmp->next;
		}
		queue = queue->next; // DANGER: LEAKS AHEAD
	}
}

t_conn	*find_path(t_lemin *l)
{
	t_conn	*path;
	t_rooms *temp;
	t_conn *i;

	path = NULL;
	pushfront(l->end, &path);
	temp = l->end;
	while (1)
	{
		if (temp == l->start)
			break ;
		i = temp->connections;
		while (i)
		{
			if (i->room->dist < temp->dist)
			{
				pushfront(i->room, &path);
				temp = i->room;
			}
			i = i->next;
		}
	}
	return (path);
}