/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 17:47:52 by opokusyn          #+#    #+#             */
/*   Updated: 2018/05/11 17:48:03 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lem_in.h"

int		main(int ac, char **av)
{
	static t_lemin	l;

	store_line((char *)&l);
	l.fd = av[1] ? open(av[1], O_RDONLY) : 0;
	get_ants(&l);
	get_rooms(&l);
	validation(&l);
	get_links(&l);
	t_path *all_paths = find_paths(&l);
	print_content(&l);
	t_ants *ants = ant_farm(all_paths, &l);
	ants_iter(ants);
	system("leaks lem_in");
	return (0);
}