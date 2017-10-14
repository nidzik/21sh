#include "glob.h"
#include "../minishell.h"

char *ft_check_files(char *woord)
{
    char **files_tab;
    int j;
    char * found;
    char *final;

    final = NULL;
    found = NULL;
    j = 0;
    files_tab = NULL;
    files_tab = ft_list_file_check();
    while (files_tab != NULL && files_tab[j] != NULL)
    {
        if (final == NULL)
        {
            if (ft_strstr(files_tab[j], woord) != NULL)
                if (mystrstr(files_tab[j], woord, ft_strlen(woord)) == 0)
                    final = ft_strdup(files_tab[j]);
        }
        else if (final != NULL &&                                       \
                 mystrstr(files_tab[j], woord,ft_strlen(woord)) == 0)
            final = ft_add_next_word(found, files_tab[j], final);
        j++;
    }
    ft_free_tab(files_tab);
    return (final);
}

char *ft_check_files_end(char *woord)
{
    char **files_tab;
    int j;
    char * found;
    char *final;

    final = NULL;
    found = NULL;
    j = 0;
    files_tab = NULL;
    files_tab = ft_list_file_check();
    while (files_tab != NULL && files_tab[j] != NULL)
    {
        if (final == NULL)
        {
            if (ft_strstr(files_tab[j], woord) != NULL)
                if (ft_strncmp(files_tab[j], woord, ft_strlen(woord)) == 0)
                    final = ft_strdup(files_tab[j]);
        }
        else if (final != NULL &&                                       \
                 ft_strncmp(files_tab[j], woord,ft_strlen(woord)) == 0)
            final = ft_add_next_word(found, files_tab[j], final);
        j++;
    }
    ft_free_tab(files_tab);
    return (final);
}
