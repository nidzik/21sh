#include "minishell.h"

void        move_cursor_left(void)
{
    t_point *cursor_pos;
    int i;

    i = 1;
    cursor_pos = ft_get_cursor();
    if (cursor_pos->x == 1)
    {
        tputs(tgetstr("up", NULL),1,my_out);
        while (i <= ft_get_win_x()-2)
        {
            i++;
            tputs(tgetstr("nd", NULL),1,my_out);
        }
    }
    else
        tputs(tgetstr("le", NULL),1,my_out);
    free(cursor_pos);
}
