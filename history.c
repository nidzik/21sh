#include "minishell.h"


t_hist *ft_init_histo()
{
	t_hist *h;

	h = NULL;
	if(!(h = (t_hist *)malloc(sizeof(t_list))))
		return (NULL);
	h->next = NULL;
	h->curr = 0;
	h->prev = NULL;
	h->line = NULL;
	return (h);
}

t_hist	*ft_add_history(t_hist *h, char *line)
{
	if (h != NULL && !h->next && !h->prev && !h->line)
	{
		
		h->line = ft_strdup(line);
		return (h);
	}
	if (h != NULL)
		while (h->next != NULL)
			h = h->next;
	h->next = ft_init_histo();
	h->next->prev = h;
	h = h->next;
	h->line = ft_strdup(line);

    h->next = NULL;
   	return (h);
}

void	ft_next_hist(t_hist *h)
{
	if (h && h->prev != NULL)
		h = h->prev;
}
void	ft_roll_back_histo(t_hist *h)
{
	if (h != NULL)
		while (h->next != NULL)
			h = h->next;
	
}
t_hist	*ft_print_next_histo(t_hist *h, t_line *li)
{
	if (h != NULL && h->line != NULL)
	{
		if (h->curr == 1 && h->prev)
		{
			h->curr = 0;
			h = h->prev;
		}
//		else if (h->curr == 0)
			
		ft_cursor_start(li->cursor);
		tputs(tgetstr("cd", NULL), 1, my_out);
		
			
		ft_bzero(li->buf, ft_strlen(li->buf));
        ft_strncpy(li->buf, h->line, ft_strlen(h->line));
		li->len_max = ft_strlen(h->line);
        li->cursor = 0;
		ft_print_all_buf(li->buf, li->cursor, li->len_max);
		li->cursor = li->len_max;
		if (h->prev && h->curr == 0)
		{
			h = h->prev;
			h->curr = 1;
		}
//		ft_cursor_end(li->cursor, li->len_max);
//				fflush(stdout);
		return (h);
	}
	return (h);
}

t_hist	*ft_print_prev_histo(t_hist *h, t_line *li)
{
	if (h != NULL && h->next != NULL && h->next->line != NULL)
	{

		ft_cursor_start(li->cursor);
		tputs(tgetstr("cd", NULL), 1, my_out);
//				ft_cursor_start(li->cursor);
		h->curr = 0;
		h = h->next;
		h->curr = 1;
		ft_bzero(li->buf, ft_strlen(li->buf));
		ft_strncpy(li->buf, h->line, ft_strlen(h->line));
		li->len_max = ft_strlen(h->line);
		li->cursor = 0;

//		tputs(tgetstr("nw", NULL), 1, my_out);
//		tputs(tgetstr("cd", NULL), 1, my_out);
//		h = h->next;
		ft_print_all_buf(li->buf, li->cursor, li->len_max);
		li->cursor = li->len_max;
//		ft_putstr("GG");
//		ft_cursor_end(li->cursor, li->len_max);
//		ft_putstr(h->line);
		fflush(stdout);
		return (h);
	}
	return (h);
}
