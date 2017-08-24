#include "minishell.h"

static int		ft_listsize(t_env *e)
{
	t_env	*s;
	int		i;

	i = 0;
	s = e;
	if (e != NULL)
	{
		while (s != NULL)
		{
			i++;
			s = s->next;
		}
	}
	return (i);
}

char	**ft_list_to_tab(t_env *e)
{
	char	**tstr;
	char	*stock;
	t_env	*s;
	int		i;

	s = e;
	if (e == NULL)
		return (NULL);
	i = ft_listsize(e);
	if (!(tstr = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (s != NULL)
	{
		stock = ft_strjoin(s->name, "=");
		tstr[i] = ft_strjoin(stock, s->value);
		ft_strdel(&stock);
		i++;
		s = s->next;
	}
	tstr[i] = NULL;
	return (tstr);
}

void replace_value_in_env(t_env *e, char *name, char *new_value)
{
	t_env *s;

	s = e;
	while (s)
	{
		if (ft_strncmp(name, s->name, ft_strlen(s->name)) == 0)
		{
			ft_strdel(&s->value);
			s->value = ft_strdup(new_value);
			return;
		}
		else
			s = s->next;
	}
}

char *find_value_in_env(t_env *e, char *name)
{
    t_env *s;

    s =	e;
    while (s)
    {
    	if (ft_strncmp(name, s->name, ft_strlen(s->name)) == 0)
        {
            return (s->value);
		}
		else
			s = s->next;
    }
	return (NULL);
}
