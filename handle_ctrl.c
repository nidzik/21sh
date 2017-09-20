#include "minishell.h"

int ft_handle_ctrl(t_line *li)
{
	if (CTRL_K)
		ft_ctrl_k(li);
	else if (CTRL_U)
		ft_ctrl_y(li);

	return 0;
}

void ft_ctrl_k(t_line *li)
{
	int cursor;
	int j;

	j = 0;
	cursor = li->cursor;
	tputs(tgetstr("ce", NULL), 1, my_out);
	tputs(tgetstr("nw", NULL), 1, my_out);
	tputs(tgetstr("cd", NULL), 1, my_out);
	if (li->cut != NULL)
		ft_strdel(&li->cut);
	(li->cut = (char *)malloc(sizeof(char) * (li->len_max - cursor) + 1));
		while (li->buf[cursor] && cursor <= li->len_max)
		{
			li->cut[j] = li->buf[cursor];
			li->buf[cursor++] = '\0';
			j++;
		}
		li->cut[j] = '\0';
		li->len_max -= j;
}
	
void ft_ctrl_y(t_line *li)
{
	int i;
	int cur;

	cur = li->cursor;
	i = 0;
	while (li->cut[i] != '\0')
	{
		li->len_max++;
		ft_insert(li->buf, cur++, li->cut[i]);
		i++;
	}
		ft_print_buf(li->buf, li->cursor, li->len_max);
}
