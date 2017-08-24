#include "minishell.h"

void ft_exit(t_group *g)
{
	(void)g;
	ft_free_env(g->env);
	//ft_strdel(&g->name);
	//ft_strdel(&g->value);
	free(g);
	ft_putchar('\n');
	destruct();
	exit(1);
}

void ft_error(char *str)
{
    if (str)
        ft_putendl(str);
}
void ft_error_cmd(char *cmd, char *msg, char *args)
{
	if (cmd)
		ft_putstr(cmd);
	if (msg)
		ft_putstr(msg);
	if (args)
		ft_putendl(args);
	else
		ft_putchar('\n');
}
void ft_cd(t_group *g)
{
    char *cwd;
    char **arrcmd;
	char *modify;

	modify = NULL;
    arrcmd = NULL;
    cwd = NULL;
    cwd = getcwd(cwd, MAXPATHLEN);
    arrcmd = ft_split(g->cmd);
    if (arrcmd[1] == NULL)
		modify = find_value_in_env(g->env, "HOME");
	else if (arrcmd[1][0] == '~')
	{
		modify = ft_strjoin(find_value_in_env(g->env, "HOME"), ++arrcmd[1] );
		arrcmd[1]--;
	}
	else
		modify = arrcmd[1];
//	ft_putendl(modify);
    if (chdir(modify) < 0)
        ft_error_cmd(arrcmd[0], ": No such file or directory: ", arrcmd[1]);
	else
		replace_value_in_env(g->env, "OLDPWD", cwd);
		ft_strdel(&cwd);
		ft_free_tabstr(arrcmd);
}
