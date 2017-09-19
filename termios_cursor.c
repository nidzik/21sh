#include "minishell.h"

t_point *ft_get_cursor(void)
{
	char *ansi;
	char *buff;
	char *tmp;
	t_point *cursor;

	cursor = (t_point *)malloc(sizeof(t_point));
	ansi = ft_strnew(1);
	buff = ft_strnew(10);
	write(0,"\E[6n",4);
	while (ft_strchr(buff, 'R') == NULL)
	{
		ft_bzero(buff,10);
		read(0,buff,10);
		tmp = ansi;
		ansi = ft_strjoin(tmp,buff);
		ft_strdel(&tmp);
	}
	cursor->y = ft_atoi(&ansi[2]);
	cursor->x = ft_atoi(&ft_strchr(&ansi[2], ';')[1]);
	ft_strdel(&buff);
	ft_strdel(&ansi);
	return (cursor);
}

int		ft_get_cursor_x(void)
{
	char *ansi;
	char *buff;
	char *tmp;
	int x;

	x = 0;
	ansi = ft_strnew(1);
	buff = ft_strnew(10);
	write(0,"\E[6n",4);
	while (ft_strchr(buff, 'R') == NULL)
	{
		ft_bzero(buff,10);
		read(0,buff,10);
		tmp = ansi;
		ansi = ft_strjoin(tmp,buff);
		ft_strdel(&tmp);
	}
	x = ft_atoi(&ft_strchr(&ansi[2], ';')[1]);
	ft_strdel(&buff);
	ft_strdel(&ansi);
	return (x);
}

int			ft_get_cursor_y(void)
{
	char	*ansi;
	char	*buff;
	char	*tmp;
	int 	y;

	y = 0;
	ansi = ft_strnew(1);
	buff = ft_strnew(10);
	write(0,"\E[6n",4);
	while (ft_strchr(buff, 'R') == NULL)
	{
		ft_bzero(buff,10);
		read(0,buff,10);
		tmp = ansi;
		ansi = ft_strjoin(tmp,buff);
		ft_strdel(&tmp);
	}
	y = ft_atoi(&ansi[2]);
	ft_strdel(&buff);
	ft_strdel(&ansi);
	return (y);
}

