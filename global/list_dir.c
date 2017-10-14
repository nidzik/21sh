#include "glob.h"
#include "../minishell.h"

/*
** count number of files in dir `.'
** return (int)
*/
int					nb_files_in_dir(void)
{

	DIR				*d;
	struct dirent	*dir;
	int				i;

	i = 0;
	if ((d = opendir(".")) == NULL )
		return (-1);
	while ((dir = readdir(d)) != NULL)
		if (dir->d_name[0] != '.')
			i++;
	closedir(d);
	return (i);
}

/*
** get files in dir `.' put them into an array  
** return (char **)
*/
char				**ft_list_file_check(void)
{
	DIR				*d;
	struct dirent	*dir;
	int				i;
	char   			**array_files;

	i = nb_files_in_dir();
	array_files = NULL;
	array_files  = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	if ((d = opendir(".")) == NULL )
		return (NULL);
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.')
		{
			array_files[i] = ft_strdup(dir->d_name);
			i++;
		}
	}
	array_files[i] = NULL;
	closedir(d);
	return (array_files);
}
/*
** get files in dir `.' put them into an list  
** return (t_list)
*/
t_list				*ft_files_to_list(char *directory)
{
	DIR				*d;
	struct dirent	*dir;
	t_list			*list;
	
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
	return (list);
}

/*
** get files in dir `.' put them into an string with a ' ' between each 
** return (char *)
*/
char				*ft_list_file(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			*list;
	char			*ret;
	char			*tmp;

	tmp = NULL;
	ret = NULL;
	list = NULL;
	if ((d = opendir(".")) == NULL )
		return (NULL);
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.')
		{
			if (list == NULL)
			{
				tmp = ft_strjoin(dir->d_name, " ");
				list = ft_strdup(tmp);
				ft_strdel(&tmp);
			}
			else
			{
				tmp =  ft_strjoin(dir->d_name, " ");
				ret = ft_strjoin(list, tmp);
				ft_strdel(&list);
				list = ft_strdup(ret);
				ft_strdel(&ret);
				ft_strdel(&tmp);
			}
		}
	}
	closedir(d);
	return (list);
}
