#include "minishell.h"
#include "sig_term.h"

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
		    if (i == CD)
				group->cmd = cmd;
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
}

void ft_handle_line(t_built *built, t_group *group, t_path *path)
{
	char **split;
	int status;
	pid_t father;
	char *liness;
	char *path_cmd;
	
	status = 0;
	while (get_next_line(0, &liness) > 0)
	{
		/* if ((ret = ft_parse_line(ft_strtrim(lines), parse)) == 0) */
		status = 0;
		if (ft_strlen(liness) == 0 || ft_check_built(liness, built, group) != NULL)
			;
		else if (  ((path_cmd = find_cmd_in_path(liness, path)) != NULL))
			{
				father = fork();
				if (father > 0)
				{
					wait(&status);
					ft_putendl("exit");
				}
				if (father == 0)
				{
					//signal(SIGINT,ft_ctrl_c_fork);
					if (ft_strlen(liness) > 0)
					{
						split =  ft_split(liness);
						
						execve(path_cmd, split++, ft_list_to_tab(group->env));

						ft_free_tabstr(split);
						//exit(1);
					}

					exit(1);
				}
			}
			else
				ft_putendl("command not found");
			ft_strdel(&liness);
			//			ft_putstr("$> ");	
			/*}
		else if (ret == 1)
			ft_putstr("> ");
		else
		*/
			ft_putstr("$> ");
	}
}
