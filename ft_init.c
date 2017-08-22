#include "minishell.h"

t_parse			*ft_init_parse_struct(void)
{
	t_parse		*parse;

	parse = (t_parse *)malloc(sizeof(t_parse));
	parse->next = NULL;
	parse->delimitor = (t_delimitor *)malloc(sizeof(t_delimitor));
	parse->delimitor->simple_q = 0;
	parse->delimitor->double_q = 0;
	parse->delimitor->bracie_l = 0;
	parse->delimitor->bracie_r = 0;
	parse->delimitor->parent_l = 0;
	parse->delimitor->parent_r = 0;
	return (parse);
}
