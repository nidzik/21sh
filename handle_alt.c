#include "minishell.h"

void		ft_handle_alt(t_line *li)
{
	if (ALT_R)
		ft_handle_alt_r(li);
	else if (ALT_L)
		ft_handle_alt_l(li);
	else if (ALT_U)
		ft_handle_alt_u(li);
	else if (ALT_D)
		ft_handle_alt_d(li);
}
void	 	ft_handle_alt_r(t_line *li)
{
    int		i;
    t_point	*cursor_pos;

    i = li->cursor;
    if (ALT_R)
    {
        while (li->buf[i] == ' ')
        {
            cursor_pos = ft_get_cursor();
            if (cursor_pos->x == ft_get_win_x()-1)
                tputs(tgetstr("do", NULL),1,my_out);
            else
                tputs(tgetstr("nd", NULL),1,my_out);
            i++;
        }
        while (ft_isalnum(li->buf[i]) == 1)
        {
            cursor_pos = ft_get_cursor();
            if (cursor_pos->x == ft_get_win_x()-1)
                tputs(tgetstr("do", NULL),1,my_out);
            else
                tputs(tgetstr("nd", NULL),1,my_out);
            i++;
        }

    }
	li->cursor = i;
}


void		ft_handle_alt_l(t_line *li)
{
	int		i;
	t_point     *cursor_point;
	
	i = li->cursor;
	cursor_point = ft_get_cursor();
	if (ALT_L)
	{
		if (i  > 0)
		{
			move_cursor_left()		;
			i--;
		}
		while ((li->buf[i] == ' ') && (i > 0) )
		{
			move_cursor_left();
			i--;
		}
		while (ft_isalnum(li->buf[i]) == 1 && i > 0)
		{
			if (li->buf[i-1] == ' ' || i == 0)
				break;
			move_cursor_left();
			i--;
		}

	}
	li->cursor = i;
	free(cursor_point);
}

void			ft_handle_alt_u(t_line *li)
{
	int			save_cursor_pos;
	t_point		*cursor_point;
	int 		i;

	i = li->cursor;
	save_cursor_pos = li->cursor;
	cursor_point = ft_get_cursor();
	while (i >= 0)
	{	
		i--;
		cursor_point->x--;
		if (cursor_point->x <= 0 && \
			( ft_get_win_x() + cursor_point->x == ft_get_cursor()->x))
		{
			while (save_cursor_pos != i)
			{
				move_cursor_left();
				save_cursor_pos--;
			}
			li->cursor = i;
		}
	}
	free(cursor_point);
}

void		ft_handle_alt_d(t_line *li)
{
	int			save_cursor_pos;
	t_point		*cursor_point;
	int 		i;

	i = li->cursor;
	save_cursor_pos = li->cursor;
	cursor_point = ft_get_cursor();
	while (i <= li->len_max)
	{	
		i++;
		cursor_point->x++;
		if (cursor_point->x >= ft_get_win_x() && \
			( cursor_point->x - ft_get_win_x() == ft_get_cursor()->x))
		{
			while (save_cursor_pos != i)
			{
				if (ft_get_cursor()->x == ft_get_win_x())
					tputs(tgetstr("do", NULL),1,my_out);
				else
					tputs(tgetstr("nd", NULL),1,my_out);
				save_cursor_pos++;
			}
			li->cursor = i;
		}
	}
	free(cursor_point);
}
