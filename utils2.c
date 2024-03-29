#include "minishell.h"

t_line *ft_handle_key_code(t_line *li)
{
	t_point *cursor_pos;
	int i;

	i = 0;
	/*ft_putnbr(li->tmp[0]);
			ft_putchar(' ');
			ft_putnbr(li->tmp[1]);
			ft_putchar(' ');
			ft_putnbr(li->tmp[2]);
			ft_putchar(' ');
			ft_putnbr(li->tmp[3]);
			ft_putchar(' ');
			ft_putnbr(li->tmp[4]);
	*/	
	if ( li->tmp[3] == 126)
		li->cursor = ft_handle_fn(li->tmp, li->cursor, li->len_max);
	else if (li->tmp[0] < 25 && li->tmp[1] == 0)
		ft_handle_ctrl(li);
	else if (TMPF0)
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
		else if (UP)
			li->hist = ft_print_next_histo(li->hist, li);
		else if (DOWN)
			li->hist = ft_print_prev_histo(li->hist, li);
		else if (li->tmp[1] == 27)
		{
			ft_handle_alt(li);
			ft_putnbr(li->tmp[0]);
			ft_putnbr(li->tmp[1]);
			ft_putnbr(li->tmp[2]);
			ft_putnbr(li->tmp[3]);
			ft_putnbr(li->tmp[4]);
		}
	}
	return (li);
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

void ft_print_buf(char *buf, int cursor, int len_max)
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

void ft_print_all_buf(char *buf, int cursor, int len_max)
{
	t_point *point;
	int line;
	
	line =1;
	tputs(tgetstr("ei", NULL),1,my_out);
	point = ft_get_cursor();

	ft_cursor_start(cursor);
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
	/*
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
	*/
//	tputs(tgetstr("im", NULL),1,my_out);

}

int ft_handle_fn(char *tmp, int cursor, int len_max)
{
	int res;

	res = 0;
	if (FN_U)
	{
		//ft_putstr("gg");
		res = ft_cursor_start(cursor);
	}
	else if (FN_D)
	{
		//ft_putstr("hh");
		res = ft_cursor_end(cursor, len_max);
	}
	return (res);
}
