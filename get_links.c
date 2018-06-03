
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
	new->name1 = NULL;
	new->name2 = NULL;
	new->next = *links;
	*links = new;
}

char	*ft_substr(char *str, char sep)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	if (i > 0)
	{
		res = ft_strnew((size_t) (i));
		ft_strncpy(res, str, (size_t) (i));
	}
	return (res);
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
		l->links->name1 = ft_substr(l->line, '-');
		l->links->name2 = ft_substr(ft_strchr(l->line, '-') + 1, '\0');
//		ft_printf("%s-%s\n", l->links->name1, l->links->name2);
		t_rooms *room1 = find_room(l, l->links->name1);
		t_rooms *room2 = find_room(l, l->links->name2);
		if (room1 && room2)
		{
			if (room1 == room2)
				ft_panic(ERR_LINK_DUPLICATE);
			else
				connect_rooms(room1, room2);
		}
		else
			ft_panic(ERR_BADLINKNAME);
	}
}

