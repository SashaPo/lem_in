/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 17:00:30 by opokusyn          #+#    #+#             */
/*   Updated: 2018/05/11 17:00:32 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	find_path(t_lemin *l)
{
	t_conn *queue;

	queue = ft_memalloc(sizeof(t_conn));
	queue->room = l->start;
	ft_printf("%s\n", queue->room->name);
}