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
** ft_stock_delimitors(), in line, look for delimitor like
** ', ", (, ), {, }, [, ] if an even number of double or simple
** quote is detected, return 1 to prevent for new line
*/

int			ft_stock_delimitors(char *line, t_parse *parse)
{
	char		*string;

	ft_putendl("Enter in ft_stock_delimitor");
	string = line;
	while (*string)
	{
		ft_putchar(*string);
		ft_putchar('\n');
		if ((string = ft_strchr(string, '\'')) != NULL)
			parse->delimitor->simple_q += 1;
		else if ((string = ft_strchr(string, '\"')) != NULL)
			parse->delimitor->double_q += 1;
	//	*string++;
	}
	ft_putstr("simple quote :");
	ft_putnbr(parse->delimitor->simple_q);
	ft_putchar('\n');
	ft_putstr("double quote :");
	ft_putnbr(parse->delimitor->double_q);
	ft_putchar('\n');
	if ((parse->delimitor->simple_q % 2) != 0 ||
					(parse->delimitor->double_q % 2) != 0)
		return (1);
	return (0);
}

/*
** ft_need_more_read(), check if 2 last charactere aren't '&&'
** or last '|' and call ft_stock_delimitors() to save every
** delimitors in line.
** return (1) if a read is forbidden or return (0).
*/

int			ft_need_more_read(char *line, t_parse *parse)
{
	ft_putendl("Enter in ft_need_more_read()");
	if (line[ft_strlen(line) - 1] == '&' && line[ft_strlen(line) - 2] == '&')
		return (1);
	if (line[ft_strlen(line) - 1] == '|')
		return (1);
	if (ft_stock_delimitors(line, parse) == 1)
		return (1);
	return (0);
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
	//char		**split;
	size_t		i;

	if (line[0] == '\0' || line == NULL)
		return (-1);
	// detect 2nd line wanted
	if (ft_need_more_read(line, parse) == 1)
		return (1);
	i = ft_strlen(line);
	// if line contain space of tabulation
 	if (ft_strchr(line, ' ') != NULL)
		i = ft_strlen(line) - ft_strlen(ft_strchr(line, ' '));
	else if (ft_strchr(line, '\t') != NULL)
		i = ft_strlen(line) - ft_strlen(ft_strchr(line, '\t'));
	//split = (char *)malloc(sizeof(i) + 1);
	// if find space
	if (i != ft_strlen(line))
	{
			
	}
	else // if no space in command
	{
		// look for '=' for local var
	}
/*
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
*/
	return (1);
}
