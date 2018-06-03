
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
