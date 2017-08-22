#include "minishell.h"

void ft_cd(t_group *g)
{
	(void)g;
	ft_putendl("CD");
}
void ft_error(char *str)
{
	if (str)
		ft_putendl(str);
}

/*
static char *ft_check_built(char *cmd, t_built *built, t_group *group)
{
	int i;
	char **array;

	i = 0;
	array = NULL;
	array = ft_split(cmd);
	while (i < 6 )
	{
		if (ft_strncmp(cmd, built->list_built_in[i], ft_strlen(built->list_built_in[i])) == 0)
		{
			if (i == 3)
			{
				if (array[1])
					group->name = array[1];
				else
					ft_error("usage : unsetenv variable");
			}
			else if (i == 4)
			{
				if (array[1] && array[2])
				{
					group->name = array[1];
					group->value = array[2];
				}
				else
					ft_error("usage : setenv VAR value");
			}
			(*built->list_fct[i])(group);
			ft_free_tabstr(array);
			return (cmd);
			
		}
		i++;
	}
	ft_free_tabstr(array);
	return (NULL);
}*/

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

static char *find_cmd_in_path(char *cmd, t_path *path)
{
	struct stat sta;
	int status;
	char **array_cmd;
	int fd;
	char *concat;

	status = -1;
	if (cmd == NULL )
		return (NULL);
	array_cmd = ft_split(ft_strtrim(cmd));
	while (path->next != NULL)
	{
		concat = malloc(sizeof(char) * (ft_strlen(path->value) + ft_strlen(array_cmd[0]) + 2));
		ft_strcpy(concat, path->value);
		ft_strncat(concat, "/\0", 1);
		ft_strncat(concat, array_cmd[0], ft_strlen(array_cmd[0]));
		if ((fd = open(concat, O_RDONLY)) >= 0)
		{
			status = fstat(fd, &sta);
			close(fd);
		}
		if (status >= 0)
			break;
		free(concat);
		path = path->next;
	}
	free(array_cmd);
	if (status >= 0 )
		return (concat);
	else
		return (NULL);
}

int main(int ac, char **av, char **env)
{
	pid_t father;
	char *lines;
	int status;
	//	char **myenv = env;
	t_env           *list_env;
	t_path          *path;
	char *path_cmd;
	char ** split;
	t_built *built;
	t_group *group;
	t_parse *parse;

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
	status =  0;
	ft_putstr("$> ");
	while (get_next_line(0, &lines) > 0)
	{
		if ((ret = ft_parse_line(ft_strtrim(lines), parse)) == 0)
		{
			if (( (path_cmd = find_cmd_in_path(lines, path)) != NULL))
			{
				father = fork();
				if (father > 0)
				{
					wait(&status);
					printf("exec father");
				}
				if (father == 0)
				{
					split =  ft_split(ft_strtrim(lines));
					execve(path_cmd, split++, env);
					ft_free_tabstr(split);
				}
			}
			else
				ft_putendl("command not found");
			ft_strdel(&lines);
			ft_putstr("$> ");	
		}
		else if (ret == 1)
			ft_putstr("> ");
		else
			ft_putstr("$> ");				
	}
	ft_exit(group);
	return (0);
}
