/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 18:38:45 by opokusyn          #+#    #+#             */
/*   Updated: 2018/05/17 18:38:50 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		validation(t_lemin *l)
{
	if (l->rooms == NULL)
		ft_panic("no rooms!\n");
	else if (l->start == NULL)
		ft_panic("no start!\n");
	else if (l->end == NULL)
		ft_panic("no end!\n");
	return (1);
}

t_bool	is_numeric(const char *str)
{
	int		i;
	t_bool	spaces;

	i = 0;
	spaces = TRUE;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			i++;
		else
			spaces = FALSE;
		if (str[i] < 48 || str[i] > 57)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ft_panic(char *massage)
{
	ft_putstr_fd(massage, 2);
	exit(1);
}
