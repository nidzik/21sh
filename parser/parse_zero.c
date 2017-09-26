#include "minishell.h"

t_exec  *ft_push_mask_v1(t_term *term, t_exec *exe, char *str)
{
    exe->mask = ft_strdup(str);
    exe->cmd = ft_cmd_building(term, exe);
    if (exe->cmd == NULL)
        ft_strdel(&(exe->mask));
    else
    {
        exe->next = ft_new_exe();
//      ft_free_quot(exe->quot);
        exe = exe->next;
    }
    term->i++;
    return (exe);
}

t_exec	*ft_push_mask_v2(t_term *term, t_exec *exe, char *str)
{
    exe->mask = ft_strdup(str);
    exe->cmd = ft_cmd_building(term, exe);
    if (exe->cmd == NULL)
        ft_strdel(&(exe->mask));
    else
    {
        exe->next = ft_new_exe();
        //ft_free_quot(exe->quot);
        exe = exe->next;
    }
    term->i += 2;
    return (exe);
}

t_exec  *ft_push_mask(t_term *term, t_exec *exe, char *str)
{
    exe->mask = ft_strdup(str);
    exe->cmd = ft_cmd_building(term, exe);
    if (exe->cmd == NULL)
        ft_strdel(&(exe->mask));
    else
    {
        exe->next = ft_new_exe();
//      ft_free_quot(exe->quot);
        exe = exe->next;
    }
    return (exe);
}

t_exec	*ft_simple_redirection(t_term *term, t_exec *exe)
{
	term->p[0] = term->i;
	term->p[1] = ++term->i;
	exe = ft_get_arg(term, exe);
	if (term->line[term->i] == '>')
		exe = ft_right_redirection(term, exe);
	else
		exe = ft_left_redirection(term, exe);
	return (exe);
}

t_exec	*ft_multi_redirection(t_term *term, t_exec *exe)
{
	char	*tmp;

	term->p[0] = term->i;
	term->p[1] = term->i + 4;
	tmp = ft_strsub(term->line, term->p[0], term->p[1]);
	exe = ft_push_mask(term, exe, tmp);
	ft_strdel(&tmp);
	term->i += 4;
	return (exe);
}
