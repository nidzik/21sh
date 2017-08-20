#ifndef MINI_H
# define MINI_H

#include "libft/libft.h"
#include "get_next_line.h"
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int         get_next_line(const int fd, char **line);
int         ft_count_rows(char *name);

typedef enum			e_cmd_state
{
	ERROR = 0,
	TO_EXECUTE = 1,
	SAVE_OUTPUT = 2,
	SAVE_RESULT = 3,
	BUILT_IN = 4,
	LOCAL_VAR = 5,
	ENV_VAR = 6
}				t_cmd_state;

/*
** s_parse struct is use to handle parsing of
** line read from shell prompt.
** It stock delimitors, commands to execute,
** variable set, etc .. All instructions that
** must be excuted by this program.
*/
typedef struct			s_parse
{
	struct s_parse		*next;
	struct s_delimitor	*delimitor;
	char			*command;
	char			*argument;
	t_cmd_state		cmd_state;
	
}				t_parse;

/*
** s_delimitor struct is use to handle multiple
** delimitors in shell command, by stocking
** containor between 2 delimitor and list
** all delimitors in commands.
*/
typedef struct			s_delimitor
{
	struct s_delimitor	*next;
	char			delimitor;
	char			*contain;
}				t_delimitor;

typedef struct			s_loc_var
{
	struct s_loc_var	*next;
	char				*name;
	char				*value;
}						t_loc_var;

typedef struct			s_env
{
	struct s_env		*next;
	char				*name;
	char				*value;
}						t_env;

typedef struct			s_path
{
	struct s_path		*next;
	char				*value;
	int					valid;
}						t_path;

typedef struct			s_group
{
	t_env				*env;
	t_loc_var			*loc_var;
	char				*name;
	char				*value;
}						t_group;

typedef struct			s_built
{
	char *list_built_in[7];
    void (*list_fct[7])(t_group *);
}						t_built;

void					ft_stock_env(t_env *list_env, t_path *path, char **envp);
void					ft_stock_path(t_path *path, char *path_value);
void					ft_setenv(t_group *g);
void					ft_unsetenv(t_group *g);
void					ft_print_env(t_group *g);
int					ft_parse_line(char *line, t_parse *parse);

#endif
