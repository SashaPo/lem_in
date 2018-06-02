#include "lem_in.h"

void	print_rooms(t_lemin *l)
{
    t_rooms *copy;
    t_conn *conn_iter;

    copy = l->rooms;
    while(copy)
    {
        ft_printf("room name: %s [", copy->name);
        conn_iter = copy->connections;
        while (conn_iter)
        {
            ft_printf("%s ", conn_iter->room->name);
            conn_iter = conn_iter->next;
        }
        ft_printf("]\n");
        copy = copy->next;
    }
}

void	print_connections(t_conn *begin_con)
{
    while (begin_con)
    {
        ft_printf("%s ", begin_con->room->name);
        begin_con = begin_con->next;
    }
    ft_printf("]\n");
}

void    ft_panic(char *massage)
{
    ft_putstr_fd(massage, 2);
    exit(1);
}

void	this_is_error(void)
{
    write(1, "ERROR\n", 6);
    exit(1);
}

void	print_content(t_lemin *l)
{
    t_list *copy;

    copy = l->content_list;
    while (copy)
    {
        ft_printf("%s\n", copy->content);
        copy = copy->next;
    }
}
