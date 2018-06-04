/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remover.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:21:11 by opokusyn          #+#    #+#             */
/*   Updated: 2018/06/04 14:21:26 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reset_graph(t_rooms *rooms)
{
	while (rooms)
	{
		rooms->visited = FALSE;
		rooms = rooms->next;
	}
}

void	remove_if(t_conn **begin, t_rooms *del)
{
	t_conn	*tmp;
	t_conn	*cur;
	t_conn	*prev;

	if ((*begin)->room == del)
	{
		tmp = *begin;
		*begin = (*begin)->next;
		ft_memdel((void **)&tmp);
	}
	cur = *begin;
	prev = *begin;
	while (cur)
	{
		if (cur->room == del)
		{
			prev->next = cur->next;
			ft_memdel((void **)&cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	remove_conn(t_rooms *curr, t_rooms *prev)
{
	if (!prev || !curr)
		return ;
	remove_if(&curr->connections, prev);
	remove_if(&prev->connections, curr);
}

void	remove_path(t_lemin *l, t_conn *path)
{
	while (path)
	{
		if (path->room != l->start && path->room != l->end)
			path->room->visited = TRUE;
		remove_conn(path->room, path->room->prev);
		path = path->next;
	}
}
