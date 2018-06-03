
#include "lem_in.h"

void	get_ants(t_lemin *l)
{
	int i;

	while (get_next_line(l->fd, &l->line) && store_line(l->line))
	{
		i = 0;
		while (l->line[i] != '\0')
		{
			if (l->line[i] < 48 || l->line[i] > 57)
				this_is_error();
			i++;
		}
		if (ft_strlen(l->line) > 10)
			ft_panic(ERR_ANTSTRINGTOOLONG);
		if (ft_atol(l->line) > 2147483647)
			ft_panic(ERR_BIGANT);
		l->ants = (int)ft_atol(l->line);
		if (l->ants <= 0)
			this_is_error();
		else
			break ;
	}

}

void	add_ant(t_ants **ants, int id, t_conn *path)
{
	t_ants *ant = ft_memalloc(sizeof(t_ants));
	ant->id = id;
	ant->path = path;
	t_ants *copy = *ants;
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
	int 	i;
	t_ants	*ants;
	t_path	*tmp;

	ants = NULL;
	i = 1;
	while (i <= l->ants)
	{
		tmp = all_paths;
		while (tmp && i <= l->ants)
		{
			add_ant(&ants, i++, tmp->path);
			tmp = tmp->next;
		}
		move_ants(ants);
	}
	return (ants);
}