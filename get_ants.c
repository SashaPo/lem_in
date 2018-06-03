
#include "lem_in.h"

void	get_ants(t_lemin *l)
{
	int i;

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
}

t_ants	*ant_farm(t_path *all_paths, t_lemin *l)
{
	int 	i;
	t_ants	*ants;

	ants = NULL;
	i = 1;
	while (i <= l->ants)
	{
		t_ants *ant = ft_memalloc(sizeof(t_ants));
		ant->id = i++;
		t_ants *copy = ants;
		if (!ants)
			ants = ant;
		else
		{
			while (copy->next)
				copy = copy->next;
			copy->next = ant;
		}
	}

}