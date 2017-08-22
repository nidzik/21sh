#include "minishell.h"

void    ft_free_path(t_path *e)
{
    t_path *f;

    if (e != NULL)
    {
        while (e != NULL)
    	{
            ft_strdel(&e->value);
     	    f = e;
            e = e->next;
            free(f);
			f = NULL;
		}
    }
}

void	ft_free_env(t_env *e)
{
	t_env *f;
	
	if (e != NULL)
	{
		while (e != NULL)
		{
			ft_strdel(&e->name);
			ft_strdel(&e->value);
			f = e;
			e = e->next;
			free(f);
			f = NULL;
		}
	}
}

void	ft_free_tabstr(char **tstr)
{
	int		i;

	if (tstr != NULL)
	{
		i = 0;
		if (tstr != NULL)
		{
			if (tstr[i] != NULL)
				while (tstr[i] != NULL)
				{
					ft_strdel(&tstr[i]);
					tstr[i] = NULL;
					i++;
				}
			free(tstr);
			tstr = NULL;
		}
	}
	else
		ft_putendl("free_tabstr fail");
}
