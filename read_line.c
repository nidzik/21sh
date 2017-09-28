#include "minishell.h"

static t_line 		*ft_handle_enter(t_line *li, t_group *group)
{
	if ( li->tmp[0] == '\r' || li->tmp[0] == '\n')
	{
		if (ft_strncmp(li->buf, "exit", 5) == 0)
		{
			while (li->hist && li->hist)
				ft_exit(group);
		}
		tputs(tgetstr("rc", NULL),1,my_out);
		if (ft_strlen(li->buf) > 0)
		{
			ft_putchar(li->tmp[0]);
			li->hist = ft_add_history(li->hist, li->buf);
			if (li->hist != NULL)
				while (li->hist->next != NULL)
					li->hist = li->hist->next;
		}
		ft_putendl(li->buf);
		li->len_max = 0;
		li->cursor = 0;
		ft_putstr("$> ");
		tputs(tgetstr("sc", NULL),1,my_out);
//		ft_bzero(li->buf, 1024);
	}
	return (li);
}

static void	ft_go_insert(int cursor, int len_max)
{
	if (cursor != len_max)
		tputs(tgetstr("im", NULL),1,my_out);
	else
		tputs(tgetstr("ei", NULL),1,my_out);
}

static t_line		*ft_add_into_buf(t_line *li)
{
	char *tmp;

	tmp = NULL;
	ft_putchar(li->tmp[0]);
	if (ft_get_cursor()->x == ft_get_win_x())
	{
		tputs(tgetstr("cd", NULL),1,my_out);
		ft_putchar('\n');
	}
	li->letter = li->tmp[0];
	li->len_max++;
	li->cursor++;
	if (li->cursor == li->len_max)
		ft_strncat(li->buf, li->tmp, 1);
	else
	{
		tputs(tgetstr("sc", NULL),1,my_out);
		tmp = ft_insert(li->buf, li->cursor, li->letter);
		ft_strdel(&(li->buf));
		li->buf = tmp;
		ft_print_buf(li->buf, li->cursor, li->len_max);
	}
	
	return (li);
}

t_line *ft_read_char(t_line *li, t_group *g, t_term *term)
{

//	struct s_term term;
	if ((li->r = read(0,li->tmp, 4)) >=0)
	{
		li = ft_handle_key_code(li);
		ft_go_insert(li->cursor, li->len_max);
		// *** HANDLE CTRL D = '\04' ***                              
		if (li->tmp[0] == EOF || li->tmp[0] == '\04')
			ft_exit(g);
		if ( li->tmp[0] == '\r' || li->tmp[0] == '\n')
		{
			li = ft_handle_enter(li, g);
			term->line = ft_strdup(li->buf);
			ft_bzero(li->buf, 1024);
			li->enter = 1;
		}
		else if (li->tmp[0] == '\t')
		{
			li = ft_tab(li);
		}
		else if ((ft_isprint(li->tmp[0]) == 1 || SPACE))
		{
			li = ft_add_into_buf(li);
		}
		ft_bzero(li->tmp,5);

	}
	else
		ft_putendl("read error");
	return (li);
}

t_line *ft_read_char2(t_line *li, t_group *g, t_term *term)
{

//  struct s_term term;
	while (42)
	{
		if ((li->r = read(0,li->tmp, 4)) >=0)
		{
			li = ft_handle_key_code(li);
			ft_go_insert(li->cursor, li->len_max);
			// *** HANDLE CTRL D = '\04' ***
			if (li->tmp[0] == EOF || li->tmp[0] == '\04')
				ft_exit(g);
			if ( li->tmp[0] == '\r' || li->tmp[0] == '\n')
			{
				li = ft_handle_enter(li, g);
				term->line = ft_strdup(li->buf);
				ft_bzero(li->buf, 1024);
				li->enter = 1;
				break;
			}
			else if ((ft_isascii(li->tmp[0]) == 1 || SPACE))
			{
				li = ft_add_into_buf(li);
			}
			else if (li->tmp[0] == '\t')
			{
				li = ft_tab(li);
			}
			ft_bzero(li->tmp,5);

		}
		else
			ft_putendl("read error");
	}
    return (li);
}
