#include "minishell.h"

void	*ft_add_history(t_hist *h, char *line)
{
	while (h->next != NULL)
		h = h->next;
	h->next = (t_hist *)malloc(sizeof(t_hist));
	h = h->next;
	h->line = ft_strdup(line);
	h->next = NULL;
	return (h->line);
}

void	ft_next_hist(t_hist *h)
{
	if (h->next != NULL)
		h = h->next;
}

void	ft_print_next_histo(t_hist *h)
{
/*	if (h != NULL)
		ft_putendl("h exist");
	else
		ft_putendl("h no exist");
	if (h->line != NULL)
	{
		ft_putendl("line exist");
	
		 ft_putstr(h->line);
	}
	else
		ft_putendl("line exist");
*/
//	ft_putstr("coucou");
	if (h != NULL && h->line != NULL)
	{
		tputs(tgetstr("rc", NULL), 1, my_out);
		tputs(tgetstr("cd", NULL), 1, my_out);
		tputs(tgetstr(h->line, NULL),1,my_out);
//		ft_putstr(h->line);fflush(stdout);
		ft_next_hist(h);
	}
}
