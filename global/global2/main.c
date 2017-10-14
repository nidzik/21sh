#include "../../minishell.h"
typedef struct 		s_list
{
	char *str;
	int pos;
	struct s_list *next;
}					t_list;
int strlchr(char *s1, char *s2, int pos)
{
	if (s1 != NULL)
	while (*s1)
	{
		
		s1++;
	}
}
int ft_search_slash(char *s1, int i)
{
	int j;

	j = 0;
	if (i != 0)
	{
		while (i > 0)
		{
			j++;
			i--;
			if (s1[i] == '/' || i == 0)
				return (j);
		}
	}
	else
		return (1);
	return (j);
}

t_list *init_list(t_list *list)
{
	list = malloc(sizeof(t_list));
	list->str = NULL;
	lis->pos = pos;
	return (list);
}
t_list *ft_add_list(t_list *l, t_list *l2)
{
	t_list *save;

	save = l;
	if (l == NULL)
		return (l2);
	else if (l2 == NULL)
		return (l);)
	while (l->next != NULL)
		l = l=>next;
	l->next = l2;
	return (save);
}
t_list *ft_sort_list_del(t_list *l)
{
	t_list *save;

	save = l;
	while (l != NULL)
	{
		if 
		l = l->next;
	}
	return (save);
}
// TODO struct with arg pos directory
void ft_handle_star(char *arg, int pos,t_list *list, char *directory)
{
	ft_putendl("handle star");
	if (ft_search_slach(arg, pos) == 1)
		list = ft_add_list(list, ft_files_to_list(directory));
	else if (ft_search_slach(arg, pos) > 1)
		pos++;

	return;
}
ft_handle_other();
int main(int ac, char **av)
{
	char *arg;
	char *directory;
	t_list *list;
	int i;
	
	i= 0;
	if (ac != 2)
		return (0);
	arg = ft_strdup(av[1]);
	list = 
	if (arg[0] == '/')
		directory = ft_strdup("/");
	else
		directory = ft_strdup(".");
	while (arg[i] != '\0')
	{
		if (arg[i] == '*')
			ft_handle_star(arg, i, list, directory);
		else if (arg[i] == '?')
			ft_handle
		else if (arg[i] == '[')

		else if (arg[i] == '{')

		else if (arg[i] == ']')

		else if (arg[i] == '}')
			
		else if (arg[i] != '/')

		else 
			ft_handle_other(arg, i);
	}

		
	ft_strdel(arg);
	return (0);
}
