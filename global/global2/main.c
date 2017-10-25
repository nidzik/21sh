#include "../../minishell.h"
#include "glob2.h"

int strlchr(char *s1, char *s2, int pos)
{
	char *save;

	save = s1;
	if (save != NULL)
	while (*save)
	{
		
		save++;
	}
	return (0);
}

// TODO struct with arg pos directory
t_core *ft_handle_star(t_core *core)
{
	ft_putendl("handle star");
	if (ft_search_slash(core->arg, core->pos) == 0)
	{
		ft_putstr("here");
//		ft_putnbr(ft_search_slash(core->arg, core->pos));
		core->list = ft_add_list(core->list, ft_files_to_list_char(core->directory, core->prev, core->pos));
		core->pos++;
//		sleep(1);
	}
	else if (ft_search_slash(core->arg, core->pos) == -1)
	{
		core->pos++;
		ft_putstr("++");
	}
	core->prev = '*';
	return (core);
}

t_core *ft_handle_other(t_core *core)
{
	t_listt *save;
	t_core *co;
	t_listt *prev;

	co = NULL;
	ft_putendl("handle other");
	prev = NULL;
	co = core;
	save = core->list;
		if (core->prev == 0)
			ft_putendl("help");
	if (core->prev == '*')
	{
		while (core->list != NULL)
		{
			ft_putstr("prev=*");
			if (ft_strchr(core->list->str, core->arg[core->pos]) != NULL)
			{
				core->list->pos = mystrchr(core->list->str, core->arg[core->pos]);
							core->list = core->list->next;
			}
			else
			{
				ft_putendl("delete in other");
				core->list = ft_list_del(core->list, prev);
//				printl(core->list);
			}
			prev = core->list;
		core->list = core->list->next;
		}
					core->list = save;
	}
	else if (core->pos == 0 || ft_search_slash(core->list->str, core->pos) == 1)
	{
		core->list = ft_add_list(core->list, ft_files_to_list_char(core->directory, core->arg[core->pos], core->pos));
		ft_putendl("pass");
	}
//	printl(core->list);

/*    while (core->list != NULL)
    {
        ft_putendl(core->list->str);
        core->list = core->list->next;
	}
*/	
	core->pos++;
//	core->list = save;
	return (core);
}

t_core *init_core(char *arg)
{
	t_core *core;

	ft_putendl("init core");
	core = malloc(sizeof(t_core));
	if (core == NULL)
		return (NULL);
	core->arg = ft_strdup(arg);
	core->list = NULL;
	core->pos = 0;
	core->prev = '\0';
	if (arg[0] == '/')
        core->directory = ft_strdup("/");
    else
        core->directory = ft_strdup(".");
	return (core);
}

int main(int ac, char **av)
{
	t_core *core = NULL;
	t_listt *cc = NULL;

	
	if (ac != 2)
		return (0);

	core = init_core(av[1]);
	while (core->arg[core->pos] != '\0')
	{
		ft_putendl("boucle");
		ft_putendl(core->arg);
		if (core->arg[core->pos] == '*')
			core = ft_handle_star(core);
		else if (core->arg[core->pos] == '?')
			;
		else if (core->arg[core->pos] == '[')
			;
		else if (core->arg[core->pos] == '{')
			;
		else if (core->arg[core->pos] == ']')
			;
		else if (core->arg[core->pos] == '}')
			;
//		else if (core->arg[core->pos] != '/')
//			;
		else 
			core = ft_handle_other(core);

	ft_putendl("\n\nprint list main");
		cc = core->list;
				printl(cc);
				ft_putchar('\n');
		cc = NULL;
	}
//hh
/*	while (core->list != NULL)
    {
		if (core->list->str != NULL)
        ft_putendl(core->list->str);
        core->list = core->list->next;
		}		*/
	ft_strdel(&(core->arg));
//	printl(core->list);
	return (0);
}
