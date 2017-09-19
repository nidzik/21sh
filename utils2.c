#include "minishell.h"

int ft_handle_key_code(t_line *li)
{
	t_point *cursor_pos;
	int i;

	i = 0;
	if (TMPF0)
	{
		if (RIGHT && (li->cursor < li->len_max))
		{

			cursor_pos = ft_get_cursor();
			if (cursor_pos->x == ft_get_win_x()-1)
				tputs(tgetstr("do", NULL),1,my_out);
			else
				tputs(tgetstr("nd", NULL),1,my_out);
			li->cursor++;
		}
		else if (LEFT && (li->cursor > 0))
		{
			cursor_pos = ft_get_cursor();
			if (cursor_pos->x == 1)
			{
				i = li->cursor;
				tputs(tgetstr("up", NULL),1,my_out);
				while (ft_get_cursor()->x <= ft_get_win_x()-2)
				{
					tputs(tgetstr("nd", NULL),1,my_out);
					i--;
				}
				li->cursor--;
			}
			else
			{

				tputs(tgetstr("le", NULL),1,my_out);
				li->cursor--;
			}
		}
		else if (li->tmp[1] == 27)
		{
			ft_handle_alt(li);
/*			ft_putnbr(li->tmp[1]);
			ft_putnbr(li->tmp[2]);
			ft_putnbr(li->tmp[3]);
			ft_putnbr(li->tmp[4]);*/
		}

	}
	return (li->cursor);
}

void debug(char *filename, char *print)
{
	char str[2000];
	ft_bzero(str,2000);
	ft_strcpy(str, "echo ");
	ft_strncat(str, print, ft_strlen(print));
	ft_strncat(str, " >> ",4);
	ft_strncat(str, filename, ft_strlen(filename));
	system(str);
	ft_bzero(str,2000);
}

void ft_print_buf(char *buf, int cursor, int len_max, t_point *p)
{
	t_point *point;
	int line;
	
	line =1;
	tputs(tgetstr("ei", NULL),1,my_out);
	point = ft_get_cursor();

	while (cursor < len_max)
	{
		point = ft_get_cursor();
		if (point->x == ft_get_win_x())
		{
			tputs(tgetstr("cd", NULL),1,my_out);
			if (ft_get_cursor()->y == ft_get_win_y())
			{
				line++;
				tputs(tgetstr("sf", NULL),1,my_out);
			}
			else
				ft_putchar_fd('\n',0);
			//i++;
		}
		free(point);
		ft_putchar_fd(buf[cursor],0);
		cursor++;
	}
	/* ** if no sf line == 1 just rc ** */
	if (line == 1)
		tputs(tgetstr("rc", NULL),1,my_out);
	else if (line > 1)
	{
		tputs(tgetstr("rc", NULL),1,my_out);
		while (line != 1)
		{
			tputs(tgetstr("up", NULL),1,my_out);
			line--;
		}
	}

	tputs(tgetstr("im", NULL),1,my_out);

}

int	ft_cursor_end(int cursor, int len_max)
{
	while (cursor < len_max)
	{
		ft_move_cursor_right();
		cursor++;
	}
}
