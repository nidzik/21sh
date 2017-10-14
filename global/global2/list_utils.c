#include "glob2.h"
#include "../../minishell.h"

t_core *ft_sort_list_del(t_core *core)
{
    t_listt *save;
	int i;

	i = core->list->pos;
    save = core->list;
	while (core->list->str[i] != '\0')
	{
		if(core->list->str[i] == core->arg[core->pos])
		{
			core->list->pos = i;
			core->list = save;
			return (core);
		}
		else if (core->list->str[i] != core->arg[core->pos])
		{
			
		}
		i++;
	}
	if (core->list->str[i] == '\0')
		;
//		ft_strdellist();
    return (core);
}

t_listt *ft_list_del(t_listt *l1, t_listt *prev)
{
	t_listt *tmp;

	tmp = NULL;
	if (prev == NULL)
	{
		tmp = l1->next;
		ft_strdel(&(l1->str));
		free(l1);
		return (tmp);
	}
	prev->next = l1->next;
	ft_strdel(&(l1->str));
	free(l1);
	return (prev);
}
t_listt *ft_add_list(t_listt *l, t_listt *l2)
{
    t_listt *save;

    save = l;
    if (l == NULL)
        return (l2);
    else if (l2 == NULL)
        return (l);
	while (l->next != NULL)
		l = l->next;
	l->next = l2;
	return (save);
}

int ft_search_slash(char *s1, int i)
{
    int j;

	if (i == 0 || s1[i] != '/')
		return (-1);
	else 
		return 0;
/*
    j = 0;
    if (i != 0)
    {
        while (i >= 0)
        {
            if (s1[i] == '/')
                return (j);
			else if (i == 0)
				return (j);
            j++;
            i--;
        }
    }
    else
        return (1);
		return (j);*/
}

t_listt *init_list(t_listt *list)
{
    list = malloc(sizeof(t_list));
    list->str = NULL;
    list->pos = '\0';
    return (list);
}

