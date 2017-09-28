#include "minishell.h"
#include "parser.h"

t_exec	*ft_new_exe(void)
{
	t_exec *e;

	if (!(e = (t_exec *)malloc(sizeof(t_exec))))
		return (NULL);
	e->next = NULL;
	e->cmd = NULL;
	e->mask = NULL;
	e->quot = NULL;
	e->shark = 0;
	return (e);
}

t_exec	*ft_get_arg(t_term *term, t_exec *exe)
{
	term->p[0] = term->i;
//	ft_printf(0, "[%i]", term->p[0]);

								
	while (ft_isprint(term->line[term->i]) && term->line[term->i] != ' ' &&\
		term->line[term->i] != '\t' && term->line[term->i] != ';' &&\
		term->line[term->i] != '|' && term->line[term->i] != '&' &&\
		term->line[term->i] != '>' && term->line[term->i] != '<' &&\
		term->line[term->i] != 34 && term->line[term->i] != 39 &&\
		term->line[term->i] != 0)
	{
		if (term->line[term->i] == '\\' && term->line[term->i + 1] != 0)
			term->i++;
		term->i++;
	}
	term->p[1] = term->i;
//	ft_printf(0, "[%i]\n", term->p[1]);
	exe = ft_build_quot(term, exe);
	return (exe);
}

t_exec	*ft_quot_separation(t_term *term, t_exec *exe)
{
	if (term->line[term->i++] == 34)
	{
		term->p[0] = term->i;
//		ft_printf(0, "[%i]", term->p[0]);
		while (term->line[term->i] != 34 && term->line[term->i] != 0)
			term->i++;
//		ft_printf(0, "[%i]", term->i);
		if (term->line[term->i] == 0)
			ft_dquot(term, exe);
		else
			term->p[1] = term->i;
	}
	else
	{
		term->p[0] = term->i;
		while (term->line[term->i] != 39 && term->line[term->i] != 0)
			term->i++;
		if (term->line[term->i] == 0)
			ft_quot(term, exe);
		else
			term->p[1] = term->i;
	}
	exe = ft_build_quot(term, exe);
	term->i++;
//	ft_printf(0, "[term->]");
	return (exe);
}

t_exec	*ft_num_redirection(t_term *term, t_exec *exe)
{
	int		len;

	len = ft_strlen(&(term->line)[term->i]);
	if (len == 3)
		ft_simple_redirection(term, exe);
	else if (len >= 4)
	{
		if (term->line[term->i + 2] == '&' && (term->line[term->i + 3] == '0' ||\
			term->line[term->i + 3] == '1' || term->line[term->i + 3] == '2'))
			ft_multi_redirection(term, exe);
		else
			ft_simple_redirection(term, exe);
	}
	else
//		ft_printf(2, "shell: parse error\n");
		ft_putstr_fd("shell: parse error\n", 2);
	return (exe);
}

t_exec	*ft_parse_quot(t_term *term)
{
	t_exec	*exe;
	t_exec	*s;

	exe = ft_new_exe();
	s = exe;
	term->i = 0;
	exe->quot = NULL;
	while (term->line[term->i] != 0)
	{
//									ft_putstr("coucou");
		if (term->line[term->i] == 34 || term->line[term->i] == 39)
			s = ft_quot_separation(term, s);
		else if (term->line[term->i] == ';')
			s = ft_push_mask_v1(term, s, ";");
		else if (term->line[term->i] == '>')
			s = ft_push_mask_v1(term, s, ">");
		else if (term->line[term->i] == '<')
			s = ft_push_mask_v1(term, s, "<");
		else if (term->line[term->i] == '|')
			s = ft_push_mask_v1(term, s, "|");
		else if (term->line[term->i] == '&')
			s = ft_push_mask_v1(term, s, "&");
		else if ((term->line[term->i] == '0' && (term->line[term->i + 1] == '<' || term->line[term->i + 1] == '>')) ||\
				 (term->line[term->i] == '1' && (term->line[term->i + 1] == '<' || term->line[term->i + 1] == '>')) ||\
				 (term->line[term->i] == '2' && (term->line[term->i + 1] == '<' || term->line[term->i + 1] == '>')))
			s = ft_num_redirection(term, s);
		else if (ft_isprint(term->line[term->i]) && term->line[term->i] != ' ' &&\
			term->line[term->i] != '\t')
			s = ft_get_arg(term, s);
		else
			term->i++;
	}
	
	s->cmd = ft_cmd_building(term, s);
//	ft_putstr("coucou");
//	ft_free_quote(exe->quot);
	return (exe);
}

t_exec  *ft_cmd_parcing(t_term *term)
{
	t_exec  *exe;
	t_exec	*s;
	int		i;
	char    **split;

	exe = NULL;
	split = NULL;

	if (term->line != NULL && term->line[0] != '\0')
	{
		
//		if (ft_strchr(term->line, 34) || ft_strchr(term->line, 39))

			exe = ft_parse_quot(term);

			i = 0;
			s = exe;
			while (s != NULL)
			{
				i = 0;
				if (s->cmd != NULL)
					while (s->cmd[i] != NULL)
					{
//						ft_putstr("coucou");
//						printf("[%i:%s]", i, s->cmd[i]);fflush(stdout);
						i++;
					}
//				ft_putstr("\\n\n");
				s = s->next;
			}

//		ft_printf(0, "[%s]", exe->quot->arg);
/*
		else
			split = ft_strsplit(term->line, ';');
		exe = ft_first_struct_exe(split);
		exe = ft_all_struct_exe(exe, split);
		ft_free_tabstr(split);
*/
	}
	return (exe);
}
