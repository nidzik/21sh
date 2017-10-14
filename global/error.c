#include "glob.h"
#include "../minishell.h"

t_msg *ft_error_star(t_msg *final, char *woord, char *start)
{
	char *tmp;
	tmp = ft_strjoin("minishell: no matches found: ", "*");
	final->str = ft_strjoin(tmp, woord);
	ft_strdel(&tmp);
	final->error = -1;
	ft_strdel(&woord);
	ft_strdel(&start);
	return (final);
}

t_msg *ft_error_star_end(t_msg *final, char *woord)
{
	char *tmp;
	tmp = ft_strjoin("minishell: no matches found: ", woord);
	final->str = ft_strjoin(tmp, "*");
	ft_strdel(&tmp);
	final->error = -1;
	ft_strdel(&woord);
	return (final);
}
