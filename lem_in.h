/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 17:11:12 by opokusyn          #+#    #+#             */
/*   Updated: 2018/05/11 17:11:16 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include "get_next_line.h"

typedef struct		s_rooms
{
	int				name;
	unsigned int	ant;
	int				x;
	int				y;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_links
{
	char			*name1;
	char			*name2;
	struct 	s_links	*next;
}					t_links;

typedef struct		s_lemin
{
	unsigned int	ants;
	char			*start;
	char			*end;
	char			*line;
	t_rooms			*rooms;
	t_links			*links;
}					t_lemin; 

t_lemin				ft_init_structure(t_lemin *l);
void				get_ants(t_lemin *l);
void				get_rooms(t_lemin *l);
void				get_links(t_lemin *l);
int					validation(t_lemin *l);
char				*find_path(t_lemin *l);

#endif
