#ifndef SIG_TERM_H
#define SIG_TERM_H

#include <termios.h>
#include <signal.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>

# define TMPF0		li->tmp[0] == 27
# define TMPF32		li->tmp[0] == 32
# define LEFT		(TMPF0 && li->tmp[1] == 91 && li->tmp[2] == 68)
# define UP			(TMPF0 && li->tmp[1] == 91 && li->tmp[2] == 65)
# define DOWN		(TMPF0 && li->tmp[1] == 91 && li->tmp[2] == 66)
# define RIGHT		(TMPF0 && li->tmp[1] == 91 && li->tmp[2] == 67)
# define ESC		(TMPF0 && li->tmp[1] == 0 && li->tmp[2] == 0)
# define SPACE		(TMPF32 && li->tmp[1] == 0 && li->tmp[2] == 0)
# define ALT_R		(TMPF0 && li->tmp[1] == 27 && li->tmp[2] == 91 && li->tmp[3] == 67)
# define ALT_L		(TMPF0 && li->tmp[1] == 27 && li->tmp[2] == 91 && li->tmp[3] == 68)
# define ALT_U		(TMPF0 && li->tmp[1] == 27 && li->tmp[2] == 91 && li->tmp[3] == 65)
	# define ALT_D		(TMPF0 && li->tmp[1] == 27 && li->tmp[2] == 91 && li->tmp[3] == 66)


typedef struct s_point
{
	int x;
	int y;
}				t_point;

void			ft_ctrl_c(int i);
void			ft_ctrl_d(int i);
void			ft_ctrl_c_fork(int i);
int				init(void);
void			destruct(void);
int				my_out(int i);
void			ft_exit_f(char *str);
int				ft_get_win_x(void);
int				ft_get_win_y(void);
t_point		    *ft_get_cursor(void);
#endif
