#include "minishell.h"

/*
** Check for call to local var functions()
** After get_next_line() of prompt line :
** 		- split to ' ' charactere
**		- if first strcmp(split[0], 'echo'), echo all split line
**		- if strchr(split[0], '='), create variable 
*/

/*
** ft_add_loal_var(), take name and value of new variable
** if a variable is already name in struct, edit value
*/
void				ft_add_local_var(t_group *group, char *name, char *value)
{
	t_loc_var		*loc_var;
	unsigned int	edit;

	loc_var = group->loc_var;
	edit = 0;
	while (loc_var)
	{
		if (ft_strcmp(loc_var->name, name) == 0)
		{
			loc_var->value = value;
			edit = 1;
			break ;
		}
		if (!loc_var->next)
			break;
		loc_var = loc_var->next;
	}
	if (edit == 0)
	{
		loc_var->next = (t_loc_var *)malloc(sizeof(t_loc_var));
		loc_var->next->name = name;
		loc_var->next->value = value;
		loc_var->next->next = NULL;
	}
}

/*
** ft_del_loc_var(), take variable name in arg, and check if
** it exist, if so, delete it
*/
void				ft_del_loc_var(t_group *group, char *name)
{
	t_loc_var		*prev;
	t_loc_var		*loc_var;

	prev = NULL;
	loc_var = group->loc_var;
	while (loc_var)
	{
		if (ft_strcmp(loc_var->name, name) == 0)
		{
			if (loc_var->next)
				prev->next = loc_var->next;
			else
				prev->next = NULL;
		}
		prev = loc_var;
		loc_var = loc_var->next;
	}
}

/*
** ft_parse_line(), take the line from arg (line enter in shell)
** parse it (detect quote, detect comment, built-in or not, ...)
** - return -1 if line NULL
** - return 0 if command can be executed
** - return 1 if need more read
*/
int			ft_parse_line(char *line, t_parse *parse)
{
	char		*split;
	size_t		i;

	//if (ft_strcmp(line, "\n") == 0)
	if (line[0] == '\0')
		return (-1);
	i = ft_strlen(line);
 	if (ft_strchr(line, ' ') != NULL)
		i = ft_strlen(line) - ft_strlen(ft_strchr(line, ' '));
	else if (ft_strchr(line, '\t') != NULL)
		i = ft_strlen(line) - ft_strlen(ft_strchr(line, '\t'));
	split = (char *)malloc(sizeof(i) + 1);
	parse->delimitor = (t_delimitor *)malloc(sizeof(t_delimitor));
	parse->next = NULL;
	if (i != ft_strlen(line))
	{
		
	}
/*
	if (ft_strncmp(*split, ft_strlen(*split++)), "echo")
	{
		while (*split++ != 0)
			ft_putstr(*split);
	}
	else if (ft_strnstr(*split, "=", ft_strlen(*split)) && **split != '=')
	{
		split2 = ft_split(*split, '=');
		// check if env var
		ft_add_local_var(group, *split2++, *split2);
	}
	else if ()
	{
	}
*/
	return (1);
}
