/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:37:21 by opokusyn          #+#    #+#             */
/*   Updated: 2018/06/04 14:37:25 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_ants(t_lemin *l)
{
	while (get_next_line(l->fd, &l->line) && store_line(l->line))
	{
		if (l->line && ft_strlen(l->line) && l->line[0] == '#')
			continue ;
		if (!is_numeric(l->line))
			ft_panic("[!] Error: ant number is not a valid number");
		if (ft_strlen(l->line) > 10)
			ft_panic(ERR_ANTSTRINGTOOLONG);
		if (ft_atol(l->line) > 2147483647)
			ft_panic(ERR_BIGANT);
		l->ants = (int)ft_atol(l->line);
		if (l->ants <= 0)
			ft_panic("[!] Error: no ants!!!!");
		else
			break ;
	}
	if (!l->ants)
		ft_panic("No input");
}

void	add_ant(t_ants **ants, int id, t_conn *path)
{
	t_ants	*ant;
	t_ants	*copy;

	ant = ft_memalloc(sizeof(t_ants));
	ant->id = id;
	ant->path = path;
	copy = *ants;
	if (!*ants)
		*ants = ant;
	else
	{
		while (copy->next)
			copy = copy->next;
		copy->next = ant;
	}
}

t_bool	move_ants(t_ants *ants)
{
	t_bool	moved;

	moved = FALSE;
	while (ants)
	{
		if (ants->path != NULL)
		{
			moved = TRUE;
			ants->path = ants->path->next;
			if (ants->path && ants->path->room)
				ft_printf("L%d-%s ", ants->id, ants->path->room->name);
		}
		ants = ants->next;
	}
	if (moved)
		ft_printf("\n");
	return (moved);
}

void	ants_iter(t_ants *ants)
{
	t_bool	moved;

	moved = TRUE;
	while (moved)
		moved = move_ants(ants);
}

t_ants	*ant_farm(t_path *all_paths, t_lemin *l)
{
	int		i;
	t_ants	*ants;
	t_path	*tmp;

	ants = NULL;
	i = 1;
	while (i <= l->ants)
	{
		if (l->ants - i <= all_paths->len)
			add_ant(&ants, i++, all_paths->path);
		else
		{
			tmp = all_paths;
			while (tmp && i <= l->ants)
			{
				add_ant(&ants, i++, tmp->path);
				tmp = tmp->next;
			}
		}
		move_ants(ants);
	}
	return (ants);
}
