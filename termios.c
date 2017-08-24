#include "minishell.h"
#include "sig_term.h"

/*
** print fct for tputs
*/

int			my_out(int i)
{
	putchar(i);
	return (i);
}

static void ft_exit_f(char *str)
{
	ft_putendl(str);
	exit(1);
}

int			init(void)
{
    char    *term_buffer;
    char    *termtype;
	struct termios term;

    termtype = NULL;
    term_buffer = (char *)malloc(2048 * sizeof(char));
    termtype = getenv("TERM");
    if ((void*)&term == NULL)
        ft_exit_f("Specify a terminal type with `setenv TERM `.");
    if (tgetent(term_buffer, termtype) == -1)
        ft_exit_f("Could not access the termcap data base or is not defined.");
    if (tcgetattr(0, &term) == -1)
        ft_exit_f("Failed tcgetattr!");
    tputs(tgetstr("ve", NULL), 1, my_out);
    term.c_lflag &= (unsigned long)~(ICANON );
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSADRAIN, &term) == -1)
        ft_exit_f("Failed tcsetattr!");
    return (0);
}

void        destruct(void)
{
	struct termios term;

    if (tcgetattr(0, &term) == -1)
    {
        ft_putstr("Failed tcgetattr!\n");
//        exit(1);
    }
    tputs(tgetstr("te", NULL), 0, my_out);
    tputs(tgetstr("ve", NULL), 0, my_out);
    tputs(tgetstr("cd", NULL), 0, my_out);
    term.c_lflag = (ICANON | ECHO | ISIG);
    if (tcsetattr(0, 0, &term) == -1)
    {
        ft_putstr("Failed tcsetattr\n");
        exit(1);
    }
    exit(1);
}
