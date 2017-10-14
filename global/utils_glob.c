#include "../minishell.h"

int mystrstr(char * s1, char *s2, int c)
{
    int i;
    int j;

    i  = 0;
    j = 0;
    if (s2 == NULL || s2[0] == '\0')
        return (-1);
    while (s1[i] != '\0')
    {
        if (s2[j] == s1[i])
        {
            j++;
            if (c == j)
                break ;
        }
        else
            j = 0;
        i++;
    }
    if (c == j && s1[++i] == '\0')
        return 0;
    else
        return (-1);
}

void ft_free4(char *s1, char *s2, char *s3, char *s4)
{
	if (s1 != NULL)
		ft_strdel(&s1);
	if (s2 != NULL)
		ft_strdel(&s2);
	if (s3 != NULL)
		ft_strdel(&s3);
	if (s4 != NULL)
		ft_strdel(&s4);
}

void ft_free_tab(char **arr)
{
	int i;

	i = 0;
	if (arr != NULL)
		while (arr[i] != NULL)
			ft_strdel(&arr[i++]);
	free(arr);
}

char *ft_add_next_word(char *found, char *files_tab, char *final)
{
	char *tmp;

	tmp = NULL;
	found = files_tab;
	tmp = ft_strjoin(" ", found);
	found = ft_strdup(final);
	ft_strdel(&final);
	final = ft_strjoin(found, tmp);
	ft_strdel(&found);
	ft_strdel(&tmp);
	return (final);
}

