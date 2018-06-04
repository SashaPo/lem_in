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

void	clear_path(t_conn **path)
{
	t_conn	*cur;
	t_conn	*prev;

	cur = *path;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		ft_memdel((void **)&prev);
	}
}

void	go_to(t_conn *tmp, t_conn *queue)
{
	if (tmp->room->visited != TRUE)
	{
		pushback(tmp->room, &queue);
		tmp->room->visited = TRUE;
		tmp->room->prev = queue->room;
	}
}

t_conn	*bfs(t_lemin *l)
{
	t_conn	*queue;
	t_conn	*tmp;

	queue = ft_memalloc(sizeof(t_conn));
	queue->room = l->start;
	while (queue)
	{
		queue->room->visited = TRUE;
		tmp = queue->room->connections;
		while (tmp)
		{
			go_to(tmp, queue);
			if (tmp->room == l->end)
			{
				tmp->room->prev = queue->room;
				clear_path(&queue);
				return (tmp);
			}
			tmp = tmp->next;
		}
		tmp = queue;
		queue = queue->next;
		ft_memdel((void **)&tmp);
	}
	return (queue);
}

t_conn	*find_path(t_lemin *l)
{
	t_conn	*path;
	t_rooms	*temp;

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

t_path	*find_paths(t_lemin *l)
{
	t_path	*paths;
	t_conn	*path;
	t_path	*new;

	paths = NULL;
	while ((bfs(l)))
	{
		path = find_path(l);
		new = ft_memalloc(sizeof(t_path));
		new->len = path_len(path);
		new->path = path;
		new->next = paths;
		paths = new;
		reset_graph(l->rooms);
		remove_path(l, path);
	}
	if (!paths)
		ft_panic(NOPATH);
	return (paths);
}
