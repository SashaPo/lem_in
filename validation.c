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
