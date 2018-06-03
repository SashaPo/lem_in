#include "lem_in.h"

void	ft_create_rooms(t_rooms **rooms)
{
	t_rooms *new;

	new = malloc(sizeof(t_rooms));
	ft_bzero(new, sizeof(t_rooms));
//	new->name = NULL;
//	new->connections = NULL;
	new->next = *rooms;
	*rooms = new;
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
	if (check_spaces(l))
		l->line = NULL;
	if (l->line)
	{
		ft_create_rooms(&l->rooms);
		if (l->is_end)
		{
			if (l->end)
				ft_panic("TWO ENDS");
			else
			{
				l->end = l->rooms;
				l->is_end = FALSE;
			}
		}
		if (l->is_start)
		{
			if (l->start)
				ft_panic("TWO STARTS");
			else
			{
				l->start = l->rooms;
				l->is_start = FALSE;
			}
		}
		int len = ft_strchr(l->line, ' ') - l->line;
		l->rooms->name = ft_strnew(len);
		ft_strncpy(l->rooms->name, l->line, len);
		l->rooms->x = ft_atol(ft_strchr(l->line + 1, ' '));
		if (l->rooms->x < 0 || l->rooms->x > 2147483647)
			ft_panic("not integer!!!!\n");
		l->rooms->y = ft_atol(ft_strchr(l->line + len + 2, ' '));
		if (l->rooms->y < 0 || l->rooms->y > 2147483647)
			ft_panic("not integer!!!!\n");
	}
}

t_rooms *find_room(t_lemin *l, char *name)
{
	t_rooms *copy;

	copy = l->rooms;
	while (copy)
	{
		if (ft_strcmp(copy->name, name) == 0)
		{
			return (copy);
		}
		else
			copy = copy->next;
	}
	return (copy);
}

void	connect_rooms(t_rooms *from, t_rooms *to)
{
	t_conn *confrom;
	t_conn *conto;

	confrom = ft_memalloc(sizeof(t_conn));
	conto = ft_memalloc(sizeof(t_conn));
	confrom->room = from;
	conto->room = to;
	confrom->next = to->connections;
	to->connections = confrom;
	conto->next = from->connections;
	from->connections = conto;
}

