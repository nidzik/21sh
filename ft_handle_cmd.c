#include "minishell.h"

void ft_exit(t_group *g)
{
	(void)g;
	ft_free_env(g->env);
	ft_strdel(&g->name);
	ft_strdel(&g->value);
	free(g);
	while(1);
	exit(1);
}

