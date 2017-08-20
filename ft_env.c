#include "minishell.h"

/*
** ft_print_env(), list all environment variables form t_env
** linked list
*/

void		ft_print_env(t_group * group)
{
	t_env	*env;

	env = group->env;
	while (env)
	{
		ft_putstr(env->name);
		ft_putchar('=');
		ft_putendl(env->value);
		env = env->next;
	}
}

/*
** ft_stock_env(), split environment line to name and value
** and place them in a chained list, if PATH name is find
** go stock path values
*/
void		ft_stock_env(t_env *list_env, t_path *path, char **envp)
{
	char	**env;
	char	*var_env;
	char	**split;
	t_env	*env_list;

	env = envp;
	var_env = NULL;
	env_list = list_env;
	while (*env != 0)
	{
		var_env = *env;
		split = ft_strsplit(var_env, '=');
		env_list->name = *split;
		if (ft_strcmp(*split++, "PATH") == 0)
			ft_stock_path(path, *split);
		env_list->value = *split;
		env++;
		if (*env)
		{
			env_list->next = (t_env *)malloc(sizeof(t_env));
			env_list = env_list->next;
		}
		else
			env_list->next = NULL;
	}
}

/*
** ft_stock_path(), take the full env variable path in arg
** and split it to a chained list. Check if every directory
** can be accessed.
*/
void		ft_stock_path(t_path *path, char *path_value)
{
	char	**split;
	t_path	*path_list;

	split = ft_strsplit(path_value, ':');
	path_list = path;
	while (*split != 0)
	{
		path_list->value = *split;
		if (opendir(*split) != NULL)
			path_list->valid = 1;
		else
			path_list->valid = 0;
		if (split++)
		{
			path_list->next = (t_path *)malloc(sizeof(t_path));
			path_list = path_list->next;
		}
		else
			path_list->next = NULL;
	}
}

/*
** ft_setenv(), permit to add of edit an environment variable
** if env variable already exist, var is edited else it created
*/
void		ft_setenv(t_group *g)
{
	int	set;
	t_env	*env_list;

	ft_putendl("boh");
	set = 0;
	env_list = g->env;
	while (env_list)
	{
		if (ft_strcmp(env_list->name, g->name) == 0)
		{
			env_list->value = g->value;
			set = 1;
			break ;
		}
		if (!env_list->next)
			break;
		env_list = env_list->next;
	}
	if (set == 0)
	{
		env_list->next = (t_env *)malloc(sizeof(t_env));
		env_list->next->name = g->name;
		env_list->next->value = g->value;
		env_list->next->next = NULL;
	}
}

/*
** ft_unsetenv(), take variable name in arg, and check if
** it exist, if so, delete it
*/
void		ft_unsetenv(t_env *env, char *name)
{
	t_env	*prev;
	t_env	*env_list;

	prev = NULL;
	env_list = env;
	while (env_list)
	{
		if (ft_strcmp(env_list->name, name) == 0)
		{
			if (env_list->next)
				prev->next = env_list->next;
			else
				prev->next = NULL;
		}
		prev = env_list;
		env_list = env_list->next;
	}
}
