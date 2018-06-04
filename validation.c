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
	else if (ft_strequ(l->start->name, l->end->name))
		ft_panic("start && end are the same!");
	return (1);
}

int		path_len(t_conn *path)
{
	int		len;

	len = 0;
	while (path)
	{
		len++;
		path = path->next;
	}
	return (len);
}

t_bool	is_numeric(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			i++;
		if (str[i] < 48 || str[i] > 57)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ft_panic(char *massage)
{
	ft_putstr_fd(massage, 2);
	sleep(3);
	exit(1);
}

t_bool	room_check(char *roomname, t_lemin *l)
{
	t_rooms *copy;

	copy = l->rooms;
	while (copy)
	{
		if (ft_strequ(copy->name, roomname))
			return (FALSE);
		copy = copy->next;
	}
	return (TRUE);
}
