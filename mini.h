#ifndef MINI_H
# define MINI_H

#include "libft/libft.h"
#include "get_next_line.h"
#include <dirent.h>

int         get_next_line(const int fd, char **line);
int         ft_count_rows(char *name);

typedef struct		s_env
{
	struct s_env	*next;
	char		*name;
	char		*value;
}			t_env;

typedef struct		s_path
{
	struct s_path	*next;
	char		*value;
	int		valid;
}			t_path;

typedef struct		s_group
{
	t_env *env;
	char *name;
	char *value;
}					t_group;

typedef struct		s_built
{
	char *list_built_in[7];
    void (*list_fct[7])(t_group *);
}					t_built;

void		ft_stock_env(t_env *list_env, t_path *path, char **envp);
void		ft_stock_path(t_path *path, char *path_value);
void		ft_setenv(t_env *env, char *name, char *value);
void		ft_unsetenv(t_env *env, char *name);
void		ft_print_env(t_group *group);

#endif
