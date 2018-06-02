#include "lem_in.h"

void	ft_create_rooms(t_rooms **rooms)
{
	t_rooms *new;

	new = malloc(sizeof(t_rooms));
	new->name = NULL;
	new->connections = NULL;
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
		int len = ft_strchr(l->line, ' ') - l->line;
		l->rooms->name = ft_strnew(len);

		ft_strncpy(l->rooms->name, l->line, len);
//		ft_printf("%s ", l->rooms->name);
		check_str(l);
		l->rooms->x = ft_atoi(ft_strchr(l->line + 1, ' '));
		if (l->rooms->x < 0 || l->rooms->x > 2147483647)
		{
			ft_printf("not integer!!!!\n");
			this_is_error();
		}
//		ft_printf("%d ", l->rooms->x);
		l->rooms->y = ft_atoi(ft_strchr(l->line + len + 2, ' '));
		if (l->rooms->y < 0 || l->rooms->y > 2147483647)
		{
			ft_printf("not integer!!!!\n");
			this_is_error();
		}
//		ft_printf("%d\n", l->rooms->y);
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
			break ;
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

