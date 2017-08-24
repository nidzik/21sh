#include "minishell.h"

static t_built *ft_init_built_in(t_group *group)
{
	static t_built *built;
	int i;

	(void)group;
	if ((built = malloc(sizeof(t_built))) == NULL)
	{
		ft_error("malloc error");
		ft_exit(group);
	}
	built->list_built_in[0] = NULL;
	i = 0;
	if (built->list_built_in[0] == NULL)
	{
		built->list_built_in[0] = "cd";
		built->list_fct[0] = ft_cd;		
		built->list_built_in[1] = "exit";
		built->list_fct[1] = ft_exit;
		built->list_built_in[2] = "env";
		built->list_fct[2] = ft_print_env;
		built->list_built_in[3] = "unsetenv";
		built->list_fct[3] = ft_unsetenv;
		built->list_built_in[4] = "setenv";
		built->list_fct[4] = ft_setenv;
		built->list_built_in[5] = "echo";
		built->list_built_in[6] = NULL;
	}

	return (built);
}

int main(int ac, char **av, char **env)
{
	t_env           *list_env;
	t_path          *path;
	t_built *built;
	t_group *group;
	t_parse *parse;
	int ret;
	
	ret = 0;
	ac = 0;
	(void)av;
	list_env = (t_env *)malloc(sizeof(t_env));
	path = (t_path *)malloc(sizeof(t_path));
	ft_stock_env(list_env, path, env);
	group = malloc(sizeof(group));
	group->env = list_env;
	group->name = NULL;
	group->value = NULL;
	parse = (t_parse *)malloc(sizeof(t_parse));
	built = ft_init_built_in(group);
	(*built->list_fct[2])(group);
	ft_putstr("$> ");
	ft_handle_line(built, group, path);
	ft_exit(group);
	return (0);
}
