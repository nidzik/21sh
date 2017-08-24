#include "sig_term.h"
#include "libft/libft.h"

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
