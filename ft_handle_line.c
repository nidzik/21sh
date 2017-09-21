#include "minishell.h"
#include "sig_term.h"

static char *find_cmd_in_path(char *cmd, t_path *path)
{
	struct stat sta;
	int status;
	char **array_cmd;
	int fd;
	char *concat;

	status = -1;
	if (cmd == NULL )
		return (NULL);
	array_cmd = ft_split(ft_strtrim(cmd));
	while (path->next != NULL)
	{
		concat = malloc(sizeof(char) * (ft_strlen(path->value) + ft_strlen(array_cmd[0]) + 2));
		ft_strcpy(concat, path->value);
		ft_strncat(concat, "/\0", 1);
		ft_strncat(concat, array_cmd[0], ft_strlen(array_cmd[0]));
		if ((fd = open(concat, O_RDONLY)) >= 0)
		{
			status = fstat(fd, &sta);
			close(fd);
		}
		if (status >= 0)
			break;
		free(concat);
		path = path->next;
	}
	free(array_cmd);
	if (status >= 0 )
		return (concat);
	else
		return (NULL);
}

static char *ft_check_built(char *cmd, t_built *built, t_group *group)
{
	int i;
	char **array;

	i = 0;
	array = NULL;
	array = ft_split(cmd);
	while (i < 6 )
	{
    	if (ft_strncmp(cmd, built->list_built_in[i], ft_strlen(built->list_built_in[i])) == 0)
		{
		    if (i == CD)
				group->cmd = cmd;
			if (i == 3)
			{
				if (array[1])
					group->name = array[1];
				else
					ft_error("usage : unsetenv variable");
			}
			else if (i == 4)
			{
				if (array[1] && array[2])
				{
					group->name = array[1];
					group->value = array[2];
				}
				else
					ft_error("usage : setenv VAR value");
			}
			(*built->list_fct[i])(group);
			ft_free_tabstr(array);
			return (cmd);

		}
		i++;
	}
	ft_free_tabstr(array);
	return (NULL);
}

int	ft_term_off(struct termios *term)
{
	term->c_lflag |= (ECHO | ECHOE | ICANON);
	if (tcsetattr(0, 0, term) == -1)
		return (0);
	tputs(tgetstr("ve", NULL), 1, my_out);
	return (1);
}
int	ft_term_on(struct termios *term)
{
	if (tgetent(NULL, getenv("TERM")) < 1)
		return (0);
	if (tcgetattr(0, term) == -1)
		return (0);
	term->c_lflag &= ~(ECHO | ECHOE | ICANON);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, term) == -1)
		return (0);
	tputs(tgetstr("ve", NULL), 1, my_out);
	return (1);
}
char	*ft_strrncpy(char *dst, char *src, size_t n)
{
	size_t i;

	i = 0;
	while (i <= n)
	{
		i++;
	}
//	ft_putnbr(i);

	while (src[i-1])
	{
		dst[i] = src[i-1];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
char *ft_insert(char *string, int pos_cursor, char letter)
{
	char tmp[1024];
	char *let;
	int i;
	char * save;
	save = string;
	i = 0;
	let = &letter;
//	tmp = malloc(1024 * sizeof(char));
	ft_bzero(tmp,1024);
	ft_strncpy(tmp, string, 1024);
	string[pos_cursor-1] = letter;
	ft_strrncpy(string,tmp,pos_cursor-1);
	return string;
}
void ft_handle_line(t_built *built, t_group *group, t_path *path)
{
	t_line *li;
	t_point *p;
	
	li = (t_line *)malloc(sizeof(t_line));
	li->cursor = 0;
	li->hist = ft_init_histo();

	li->cut = NULL;
	li->len_max = 0;
	(void)path;
	(void)built;
	li->buf = malloc(1024 * sizeof(char));
	ft_bzero(li->buf,1024);
	ft_bzero(li->tmp,5);
	tputs(tgetstr("sc", NULL),1,my_out);
	p = ft_get_cursor();
	while(42)
	{
		if ((li->r = read(0,li->tmp, 4)) >=0)
		{

			li->cursor = ft_handle_key_code(li);
			// *** GO TO INSERT MODE ***
			if (li->cursor != li->len_max)
				tputs(tgetstr("im", NULL),1,my_out);
			else
				tputs(tgetstr("ei", NULL),1,my_out);
//			if (mtp)

			// *** HANDLE CTRL D = '\04' ***
			if (li->tmp[0] == EOF || li->tmp[0] == '\04')
				ft_exit(group);

			// *** HANDLE RETURN ***
		    if ( li->tmp[0] == '\r' || li->tmp[0] == '\n')
			{
				if (ft_strncmp(li->buf, "exit", 5) == 0)
				{
					while (li->hist && li->hist)
					ft_exit(group);
				}
				tputs(tgetstr("rc", NULL),1,my_out);
				if (ft_strlen(li->buf) > 0)
				{
					ft_putchar(li->tmp[0]);
					li->hist = ft_add_history(li->hist, li->buf);
//					ft_roll_back_histo(li->hist);
					    if (li->hist != NULL)
							while (li->hist->next != NULL)
								li->hist = li->hist->next;
//					ft_putstr(li->hist->line);
//					li->hist = li->shist;
					
//					ft_putstr("\n\n\n");

				}
				
				ft_putendl(li->buf);
				//ft_cursor_end(li->cursor, li->len_max);
				li->len_max = 0;
				li->cursor = 0;
				ft_putstr("$> ");
				tputs(tgetstr("sc", NULL),1,my_out);
				ft_bzero(li->buf, 1024);
			}
			else if (ft_isalnum(li->tmp[0]) == 1 || SPACE || li->tmp[0] == '\t')
			{



				ft_putchar(li->tmp[0]);
				if (ft_get_cursor()->x == ft_get_win_x())
				{
					tputs(tgetstr("cd", NULL),1,my_out);
					ft_putchar('\n');
				}
				li->letter = li->tmp[0];
				li->len_max++;
				li->cursor++;
				if (li->cursor == li->len_max)
					ft_strncat(li->buf, li->tmp, 1);
				else
				{
					tputs(tgetstr("sc", NULL),1,my_out);
					//tputs(tgetstr("cd", NULL),1,my_out);

					ft_insert(li->buf, li->cursor, li->letter);
					ft_print_buf(li->buf, li->cursor, li->len_max);
					//tputs(tgetstr("rc", NULL),1,my_out);

				}
			}

			ft_bzero(li->tmp,5);
		}
		else
			ft_putendl("error read");
	}
}

/*void ft_handle_line(t_built *built, t_group *group, t_path *path)
  {
  char **split;
  int status;
  pid_t father;
  char *liness;
  char *path_cmd;
  char buf[1024];

  status = 0;
  while (get_next_line(0, &liness) > 0)
  {
  //if ((ret = ft_parse_line(ft_strtrim(lines), parse)) == 0)
  status = 0;
  if (ft_strlen(liness) == 0 || ft_check_built(liness, built, group) != NULL)
  ;
  else if (  ((path_cmd = find_cmd_in_path(liness, path)) != NULL))
  {
  father = fork();
  if (father > 0)
  {
  wait(&status);
  ft_putendl("exit");
  }
  if (father == 0)
  {
  //signal(SIGINT,ft_ctrl_c_fork);
  if (ft_strlen(liness) > 0)
  {
  split =  ft_split(liness);

  execve(path_cmd, split++, ft_list_to_tab(group->env));

  ft_free_tabstr(split);
  //exit(1);
  }

  exit(1);
  }
  }
  else
  ft_putendl("command not found");
  ft_strdel(&liness);
  //			ft_putstr("$> ");
  //}
//else if (ret == 1)
//ft_putstr("> ");
//else

ft_putstr("$> ");
}
}
*/
