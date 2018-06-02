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
	if (l->rooms->name == NULL)
	{
		ft_printf("no rooms!\n");
		this_is_error();
		return(0);
	}
	if (l->start == 0)
	{
		ft_printf("no start!\n");
		this_is_error();
		return(0);
	}
	if (l->end == 0)
	{
		ft_printf("no end!\n");
		this_is_error();
		return(0);
	}
	return (1);
}
