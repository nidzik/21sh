#include "sig_term.h"
#include "stdlib.h"

void        ft_move_cursor_left(void)
{
    t_point *cursor_pos;
    int i;

    i = 1;
    cursor_pos = ft_get_cursor();
    if (cursor_pos->x == 1)
    {
        tputs(tgetstr("up", NULL), 1, my_out);
        while (i <= ft_get_win_x() - 2)
        {
            i++;
            tputs(tgetstr("nd", NULL), 1, my_out);
        }
    }
    else
        tputs(tgetstr("le", NULL), 1, my_out);
    free(cursor_pos);
}

void		ft_move_cursor_right(void)
{
	if (ft_get_cursor_x() == ft_get_win_x() - 1)
		tputs(tgetstr("do", NULL), 1, my_out);
	else
		tputs(tgetstr("nd", NULL), 1, my_out);
}


int ft_cursor_end(int cursor, int len_max)
{
    while (cursor < len_max)
    {
        ft_move_cursor_right();
        cursor++;
    }
    return (cursor);
}

int ft_cursor_start(int cursor)
{
    while (cursor > 0)
    {
        ft_move_cursor_left();
        cursor--;
    }
    return (cursor);
}
