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
	t_loc_val		*loc_var;
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
		loc_val->next = (t_loc_var *)malloc(sizeof(t_loc_var));
		loc_val->next->name = name;
		loc_val->next->value = value;
		loc_val->next->next = NULL;
	}
}

/*
** ft_del_loc_var(), take variable name in arg, and check if
** it exist, if so, delete it
*/
void				ft_del_loc_var(t_group *group, char *name)
{
	t_loc_var		*prev;
	t_loc_var		*loc_val;

	prev = NULL;
	loc_var = group->loc_var;
	while (loc_val)
	{
		if (ft_strcmp(loc_val->name, name) == 0)
		{
			if (loc_val->next)
				prev->next = loc_val->next;
			else
				prev->next = NULL;
		}
		prev = loc_val;
		loc_val = loc_val->next;
	}
}

/*
** ft_parse_line(), take the line in parameter
**
*/
void			ft_parse_line(char *lines, t_build *built, t_group *group)
{
	char		*split;
	char		*split2;

	split = ft_strsplit(lines, ' ');
	if (ft_strncmp(*split, ft_strlen(*split++)), "echo")
	{
		while (*split++ != 0)
			ft_putstr(*split);
	}
	else if (ft_strnstr(*split, "=", ft_strlen(*split)) && **split != '=')
	{
		split2 = ft_strsplit(*split, '=');
		// check if env var
		ft_add_local_var(group, *split2++, *split2);
	}
	else if ()
	{
	}
}
