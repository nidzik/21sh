#include "sig_term.h"

/*
** ft_get_win_x(), return current width of window
*/

int         ft_get_win_x(void)
{
    struct winsize  sz;
    int             win_x;

    ioctl(0, TIOCGWINSZ, &sz);
    win_x = sz.ws_col;
    return (win_x);
}

/*
** ft_get_win_y(), return current height of window
*/

int         ft_get_win_y(void)
{
    struct winsize  sz;
    int             win_y;

    ioctl(0, TIOCGWINSZ, &sz);
    win_y = sz.ws_row;
    return (win_y);
}
