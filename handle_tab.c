#include "minishell.h"

t_line *ft_tab(t_line *li)
{
	int cur_bef;
	int cur_aft;
	char *tmp;
	int save_cur;
	
	tmp = NULL;
	cur_bef = ft_get_cursor_x();
	
	ft_putchar('\t');
	cur_aft = ft_get_cursor_x();
	if (cur_aft >= ft_get_win_x() - 2)
		ft_putchar('\n');
//		tputs(tgetstr("\n", NULL),1,my_out);
	li->letter = '\t';
	li->len_max += (cur_aft - cur_bef);
	li->cursor += (cur_aft - cur_bef);
	save_cur = li->cursor;
	if (li->cursor == li->len_max)
        ft_strncat(li->buf, li->tmp, 1);
    else
    {
        tputs(tgetstr("sc", NULL),1,my_out);
		tputs(tgetstr("ic", NULL),1,my_out);
        tmp = ft_insert(li->buf, li->cursor, li->letter);
        ft_strdel(&(li->buf));
        li->buf = tmp;
		ft_print_buf(li->buf, li->cursor, li->len_max);		
		ft_cursor_start(li->cursor);
		li->cursor = 0;
		tputs(tgetstr("cd", NULL),1,my_out);
        ft_print_all_buf(li->buf, li->cursor, li->len_max);
		li->cursor = li->len_max;
		while (li->cursor != save_cur)
		{
			ft_move_cursor_left();
			li->cursor--;
		}
															
    }
	return (li);
}
