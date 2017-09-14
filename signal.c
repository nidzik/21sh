#include "sig_term.h"
//#include "libft/libft.h"
#include "minishell.h"
void ft_ctrl_c(int i)
{
	(void)i;
	ft_putstr("\n$>");
	
}

void ft_ctrl_c_fork(int i)
{
	(void)i;
	ft_putendl("^C");
	exit(1);
}

void ft_ctrl_d(int i)
{
	(void)i;
	destruct();
}

