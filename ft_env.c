#include "mini.h"

void		ft_stock_env(t_env *list_env, t_path *path, char **envp)
{
	char	**env;
	char	*var_env;
	char	**split;

	env = envp;
	var_env = NULL;
	while (*env != 0)
	{
		var_env = *env;
		split = ft_strsplit(var_env, '=');
		list_env->name = *split;
		if (ft_strcmp(*split++, "PATH") == 0)
			ft_stock_path(path, *split);
		list_env->value = *split;
		if (env++)
		{
			list_env->next = (t_env *)malloc(sizeof(t_env));
			list_env = list_env->next;
		}
		else
			list_env->next = NULL;
	}
}

void		ft_stock_path(t_path *path, char *path_value)
{
	char	**split;

	split = ft_strsplit(path_value, ':');
	while (*split != 0)
	{
		path->value = *split;
		if (opendir(*split) != NULL)
			path->valid = 1;
		else
			path->valid = 0;
		if (split++)
		{
			path->next = (t_path *)malloc(sizeof(t_path));
			path = path->next;
		}
		else
			path->next = NULL;
	}
}

int			main(int ac, char **av, char **envp)
{
	t_env		*list_env;
	t_path		*path;

	ac = 0;
	(void)av;
	list_env = (t_env *)malloc(sizeof(t_env));	
	path = (t_path *)malloc(sizeof(t_path));	
	ft_stock_env(list_env, path, envp);
	return (0);
}
