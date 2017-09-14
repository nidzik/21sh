#include "minishell.h"

t_point *ft_get_cursor(void)
{
	char *ansi;
	char *buff;
	char *tmp;
	t_point *cursor;

	cursor = (t_point *)malloc(sizeof(t_point));
	ansi = ft_strnew(1);
	buff = ft_strnew(10);
	write(0,"\E[6n",4);
	while (ft_strchr(buff, 'R') == NULL)
	{
		ft_bzero(buff,10);
		read(0,buff,10);
		tmp = ansi;
		ansi = ft_strjoin(tmp,buff);
		ft_strdel(&tmp);
	}
	cursor->y = ft_atoi(&ansi[2]);
	cursor->x = ft_atoi(&ft_strchr(&ansi[2], ';')[1]);
	ft_strdel(&buff);
	ft_strdel(&ansi);
	return (cursor);
}
/*
  void ft_go_left(t_line *li)
  {
  t_point cursor_pos;
	
  OB	while (li->buf[i] && li->cursor >= 0)
  {
  cursor_pos = ft_get_cursor();
  if (cursor_pos->x == ft_get_win_x())
  tputs(tgetstr("do", NULL),1,my_out);
  else
  tputs(tgetstr("nd", NULL),1,my_out);
  i++;
  }
  }*/
/*
  int ft_handle_alt(t_line *li)
  {
  int i;
  int space;
  t_point *cursor_pos;
	
  space = 0;
  i = li->cursor;
  if (ALT_R)
  {
  while (li->buf[i] == ' ')
  {
  cursor_pos = ft_get_cursor();
  if (cursor_pos->x == ft_get_win_x())
  tputs(tgetstr("do", NULL),1,my_out);
  else
  tputs(tgetstr("nd", NULL),1,my_out);
  i++;
  }
  while (ft_isalnum(li->buf[i]) == 1)
  {
  cursor_pos = ft_get_cursor();
  if (cursor_pos->x == ft_get_win_x())
  tputs(tgetstr("do", NULL),1,my_out);
  else
  tputs(tgetstr("nd", NULL),1,my_out);
  i++;
  }

  }
  else if (ALT_L)
  {
  if (i -1 >= 0)
  {
  tputs(tgetstr("le", NULL),1,my_out);
  i--;
  }
  while ((li->buf[i] == ' ') && (i > 0))
  {
  tputs(tgetstr("le", NULL),1,my_out);
  i--;
  }

  while (ft_isalnum(li->buf[i]) == 1 && i > 0)
  {
  if (li->buf[i-1] == ' ')
  break;
  tputs(tgetstr("le", NULL),1,my_out);
  i--;
  }
		
  }
  li->cursor = i;
  return (i);
  }
*/
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

void ft_print_buf(char *buf, int cursor, int len_max)
{
	t_point *point;
	t_point *p2;
	int nb_lines;

	nb_lines = 1;
	tputs(tgetstr("ei", NULL),1,my_out);
	point = ft_get_cursor();
//	tputs(tgetstr("rc", NULL),1,my_out);
	p2 = ft_get_cursor();
//	tputs(tgetstr("cd", NULL),1,my_out);
	while (cursor <= len_max)
	{
//		ft_putchar_fd(buf[cursor],0);
		 tputs(&buf[cursor],1,my_out);
		if (ft_get_cursor()->x == ft_get_win_x()-1)
		{
//			point->y--;
//					                  ft_putchar('\n');
//					p2->y--;
		}
		cursor++;
	}
//	tputs(buf,1,my_out);
	nb_lines += (len_max + 3 ) / ft_get_win_x();
//	debug("gg" , ft_itoa(nb_lines));
//	if (len_max > (ft_get_win_x()-4 ))
		tputs(tgoto(tgetstr("cm",NULL), point->x -1 , point->y),1,my_out);
//	else
//	tputs(tgoto(tgetstr("cm",NULL), point->x -1 , point->y),1,my_out);
	
	tputs(tgetstr("im", NULL),1,my_out);
	
}
