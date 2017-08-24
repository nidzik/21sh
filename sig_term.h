#ifndef SIG_TERM_H
#define SIG_TERM_H

#include <termios.h>
#include <signal.h>
#include <curses.h>
#include <term.h>

void ft_ctrl_c(int i);
void ft_ctrl_c_fork(int i);
int         init(void);
void        destruct(void);
#endif
