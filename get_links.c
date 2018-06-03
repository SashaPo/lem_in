
#include "lem_in.h"

int		check_spaces(t_lemin *l)
{
	int		i;
	int		spaces;

	i = 0;
	spaces = 0;
	while(l->line[i])
	{
		if (l->line[i] == ' ' && l->line[i + 1] != ' ')
			spaces++;
		i++;
	}
	if (spaces != 2)
		return(1);
	return(0);
}

void	ft_create_links(t_links **links)
{
	t_links *new;

	new = malloc(sizeof(t_links));
	new->name1 = malloc(sizeof(t_links));
	new->name2 = malloc(sizeof(t_links));
	new->next = *links;
	*links = new;
}

void	get_links(t_lemin *l)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (l->line)
	{
		ft_create_links(&l->links);
		while (l->line[i] != '-')
			l->links->name1[j++] = l->line[i++];
		j = 0;
		i = i + 1;
		while (l->line[i] != '\0')
			l->links->name2[j++] = l->line[i++];
//		ft_printf("%s-%s\n", l->links->name1, l->links->name2);
		t_rooms *room1 = find_room(l, l->links->name1);
		t_rooms *room2 = find_room(l, l->links->name2);
		if (room1 && room2)
			connect_rooms(room1, room2);
		else
			ft_panic(ERR_BADLINKNAME);
	}
}

