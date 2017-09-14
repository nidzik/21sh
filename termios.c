#include "minishell.h"
#include "sig_term.h"

/*
** print fct for tputs
*/

int			my_out(int i)
{
    int fd;

    fd = open("/dev/tty", O_RDWR);
    if (fd == -1)
    {
        write(2, "Open error\n", 11);
        exit(-1);
    }
    write(fd, &i, 1);
    close(fd);
    return (0);
}

void ft_exit_f(char *str)
{
	ft_putendl(str);
	exit(1);
}
struct termios global_term;
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
	  if (tcgetattr(0, &global_term) == -1)
        ft_exit_f("Failed global tcgetattr!");
    tputs(tgetstr("ve", NULL), 1, my_out);
//	tputs(tgetstr("am", NULL), 1, my_out);
//	tputs(tgetstr("xn", NULL), 1, my_out);
	tputs(tgetstr("bw", NULL),1,my_out);
    term.c_lflag &= (unsigned long)~(ICANON |  ECHO | ECHOE);
//	term.c_lflag |= ~(TCOFLUSH);

    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &term) == -1)
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
//    tputs(tgetstr("te", NULL), 0, my_out);
//    tputs(tgetstr("ve", NULL), 0, my_out);
    tputs(tgetstr("cd", NULL), 0, my_out);
	tputs(tgetstr("ei", NULL),1,my_out);
    term.c_lflag = (ICANON | ECHO | ECHOE| ISIG);
    if (tcsetattr(0, 0, &global_term) == -1)
    {
        ft_putstr("Failed tcsetattr\n");
        exit(1);
    }
    exit(1);
}
