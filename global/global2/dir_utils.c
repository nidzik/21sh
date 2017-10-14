#include "glob2.h"
#include "../../minishell.h"

/*
** get files in dir `.' put them into an list
** return (t_list)
*/
t_listt	*ft_files_to_list(char *directory)
{

	DIR*d;
	struct dirent*dir;
	t_listt *list;

	ft_putendl("start files to list ");
	if (list == NULL)
		list = init_list(list);
	if ((d = opendir(directory)) == NULL )
		return (NULL);
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.')
		{
			if (list->str == NULL)
				list->str = ft_strdup(dir->d_name);
			else
			{
				list->next = malloc(sizeof(char) * ft_strlen(dir->d_name));
				list = list->next;
				list->str = ft_strdup(dir->d_name);
				list->next = NULL;
			}
		}
	}
	closedir(d);
	ft_putendl("end files to list ");
	return (list);
}

t_listt	*ft_files_to_list_char(char *directory, char c, int pos)
{

	DIR*d;
	struct dirent*dir;
	t_listt *list;
	t_listt *save;

	list = NULL;
	ft_putendl("start files to list char");
	if (list == NULL)
		list = init_list(list);
	save = list;
	if ((d = opendir(directory)) == NULL )
		return (NULL);
	while ((dir = readdir(d)) != NULL)
	{

		if (dir->d_name[0] != '.' && (ft_strlen(dir->d_name) > pos && dir->d_name[pos] == c))
		{
			if (list->str == NULL)
			{
				ft_putstr("one");
				list->str = ft_strdup(dir->d_name);
				list->pos = pos;
			}
			else
			{
				ft_putstr("two");
				list->next = (t_listt *)malloc(sizeof(t_listt));
				list = list->next;
				list->pos = pos;
				list->str = ft_strdup(dir->d_name);
				list->next = NULL;
			}
		}
	}
	closedir(d);
	ft_putendl("end files to list ");

/*	list = save;
	while (list != NULL)
	{
		ft_putendl(list->str);
		list = list->next;
		}*/
	return (save);
}
