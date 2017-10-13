/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 17:01:53 by nidzik            #+#    #+#             */
/*   Updated: 2017/10/12 17:01:56 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "../minishell.h"
//#include "dirent.h"
typedef struct		s_dir
{
	char			*name;
	int				match;
	struct s_dir	*next;
}					t_dir;

t_dir				*ft_list_file_check(void)
{
    DIR             *d;
    struct dirent   *dir;
	t_dir 			*my_dir;

	my_dir = (t_dir *)malloc(sizeof(t_dir));
	mydir->name = NULL;
	my_dir->next = NULL;
    if ((d = opendir(".")) == NULL )
        return (NULL);
    while ((dir = readdir(d)) != NULL)
    {
        if (dir->d_name[0] != '.')
        {
			my_dir = ft_strdup(dir->d_name);
			
        }
    }
    closedir(d);
    return (my_dir);
}

char				*ft_list_file(void)
{
	DIR				*d;
	struct dirent	*dir;
	char 			*list;
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
				list = ret;
				ft_strdel(&tmp);
			}
		}
	}
	closedir(d);
	return (list);
}

char *ft_star_alone(char *fresh, int i)
{
	char *right;
	char *left;
	char *list_files;
	char *final;

	final = NULL;
	right = NULL;
	left = NULL;
	list_files = NULL;
	if (fresh[i] == '*' && (i > 0 && fresh[i - 1] == ' ') \
		&& (fresh[i + 1] == '\0' || fresh[i + 1] == ' ') \
		&& (i > 0 && fresh[i - 1] != '\\'))
	{
		left = ft_strsub(fresh, 0, i);
		right = ft_strsub(fresh, i + 1, ft_strlen(fresh));
		list_files = ft_list_file();
		final = ft_strjoin(left, ft_strjoin(list_files, right));
		ft_strdel(&left);
		ft_strdel(&right);
	}
	return (final);
}

char *ft_star_before(char * fresh, int i)
{
	char *final;
	char *woord;
	int i_save;
	char *new_file;
	t_dir dir;

	dir = NULL
	final = NULL;
	woord = NULL;
	i_save = i + 1;
	if (fresh[i] == '*' && ( i > 0 && fresh[i - 1] == ' ') \
		&& (fresh[i + 1] != ' ') \
		&& (i == 0 || fresh[i - 1] != '\\'))
	{
		while (fresh[i] != ' ' && fresh[i] != '\0')
			i++;
		woord = ft_strsub(fresh, i_save, i);
		dir = ft_list_file_check();
		while 
//		new_file = ft_strdup(ft_strstr());

			ft_putendl(woord);
	}
	return (final);
}

int main(int ac, char **av)
{
	char *fresh;
	int i;
	char *final;

	final = NULL;
	fresh = NULL;
	if (ac != 2)
		return (-1);
	fresh = ft_strdup(av[1]);
	while (fresh[i] != '\0')
	{
		if ((final = ft_star_alone(fresh, i)) != NULL)
		{
			i = 0;
			ft_strdel(&fresh);
			fresh = final;
		}
		else if ((final = ft_star_before(fresh, i)) != NULL)
		{
			i = 0;
			ft_strdel(&fresh);
			fresh = final;
		}
		else
			i++;
	}
			ft_putendl(fresh);
			ft_strdel(&fresh);
			ft_strdel(&final);
}

//			ft_strdel(&list_files);
//		ft_strdel(&right);
//	ft_strdel(&left);

