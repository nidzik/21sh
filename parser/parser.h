#ifndef "PARSER_H"
#define "PARSER_H"

typedef struct	s_term
{
  int		prompt;
  char		*quot;
  int		p[2];
  int		i;
  char		*mask;
  char		*line;
  struct s_hist	*hty;
  
}		t_term;

typedef struct		s_hist
{
	char		*line;
	struct s_hist	*next;
	struct s_hist	*prev;
}			t_hist;

typedef struct		s_quot
{
	char		*arg;
	struct s_quot	*next;
}			t_quot;

typedef struct		s_exec
{
	char		**cmd;
	char		*mask;
	struct s_quot	*quot;
	int		shark;
	int		i[4];
	struct s_exec	*next;
}			t_exec;


/*
**parse
*/
t_exec          *ft_new_exe(void);
t_exec          *ft_get_arg(t_term *term, t_exec *exe);
t_exec          *ft_quot_separation(t_term *term, t_exec *exe);
t_exec          *ft_num_redirection(t_term *term, t_exec *exe);
t_exec          *ft_parse_quot(t_term *term);
t_exec			*ft_cmd_parcing(t_term *term);
/*
**parse_zero
*/
t_exec          *ft_push_mask_v1(t_term *term, t_exec *exe, char *str);
t_exec          *ft_push_mask_v2(t_term *term, t_exec *exe, char *str);
t_exec		*ft_push_mask(t_term *term, t_exec *exe, char *str);
t_exec          *ft_simple_redirection(t_term *term, t_exec *exe);
t_exec          *ft_multi_redirection(t_term *term, t_exec *exe);
/*
**creat_new_exe
*/
t_exec          *ft_background(t_term *term, t_exec *exe);
t_exec          *ft_new_semicolon(t_term *term, t_exec *exe);
t_exec          *ft_pipe(t_term *term, t_exec *exe);
t_exec          *ft_right_redirection(t_term *term, t_exec *exe);
t_exec          *ft_left_redirection(t_term *term, t_exec *exe);
/*
**parse_tools
*/
int             ft_listsize_quot(t_quot *quot);
char            **ft_cmd_building(t_term *term, t_exec *exe);
t_quot          *ft_add_arg(t_term *term);
t_exec		*ft_build_quot(t_term *term, t_exec *exe);
/*
**quot
*/
void		ft_dquot(t_term *term, t_exec *exe);
void		ft_quot(t_term *term, t_exec *exe);

#endif

