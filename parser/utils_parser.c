#include "parser.h"
#include "minishell.h"

t_term *init_term(t_term *t)
{
	if (t == NULL)
	{
		t = (t_term *)malloc(sizeof(t_term));
		t->prompt = 0;
		t-> i = 0;
		t->mask = NULL;
		t->line = NULL;
		t->hist = NULL;
		t->quot = NULL;
		t->p[0] = 0;
		t->p[1] = 0;
	}
	return (t);
}
