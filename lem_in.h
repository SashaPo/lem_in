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
#include <ft_printf/ft_printf.h>
# include "libft.h"

# define ERR_BADLINKNAME "[!] Error: bad link name"
# define ERR_ANTSTRINGTOOLONG "[!] Error: ant number is too long"
# define ERR_BIGANT "[!] Error: ant number is too big"
# define NOPATH "[!] Error: no path!"

struct s_conn;

typedef struct		s_rooms
{
	char			*name;
	struct s_rooms	*prev;
	long				x;
	long				y;
	t_bool			visited;
	struct s_conn	*connections;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_conn
{
	t_rooms			*room;
	struct 	s_conn	*next;
}					t_conn;

typedef struct		s_path
{
	int 			len;
	struct 	s_conn	*path;
	struct 	s_path	*next;
}					t_path;

typedef struct		s_ants
{
	struct 	s_conn 	*path;
	int				id;
	struct 	s_ants	*next;
}					t_ants;

typedef struct		s_links
{
	char			*name1;
	char			*name2;
	struct 	s_links	*next;
}					t_links;

typedef struct		s_lemin
{
    int             fd;
    int	            ants;
	int				comment;
	t_rooms			*start;
	t_rooms			*end;
	t_bool			is_end;
	t_bool			is_start;
	char			*line;
	t_rooms			*rooms;
	t_links			*links;
    t_list          *content_list;
}					t_lemin; 

t_lemin				ft_init_structure(t_lemin *l);
void				get_ants(t_lemin *l);
void				get_rooms(t_lemin *l);
void				get_links(t_lemin *l);
void				get_comments(t_lemin *l);
int					validation(t_lemin *l);
t_conn				*find_path(t_lemin *l);
void				ft_create_links(t_links **links);
void				ft_create_rooms(t_rooms **rooms);
void				find_start_or_end(t_lemin *l);
int					check_spaces(t_lemin *l);
void	            print_rooms(t_lemin *l);
void	            print_connections(t_conn *begin_con);
void                ft_panic(char *massage);
void				print_content(t_lemin *l);
void	            this_is_error(void);
t_rooms 			*find_room(t_lemin *l, char *name);
void				connect_rooms(t_rooms *from, t_rooms *to);
t_bool				bfs(t_lemin *l);
void				reset_graph(t_rooms *rooms);
void				remove_if(t_conn **begin, t_rooms *del);
void				remove_path(t_lemin *l, t_conn *path);



#endif
