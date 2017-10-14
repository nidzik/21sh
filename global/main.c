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

char *ft_star_alone(char *fresh, int i)
{
	char *right;
	char *left;
	char *list_files;
	char *final;
	char *tmp;
	
	final = NULL;
	right = NULL;
	left = NULL;
	tmp = NULL;
	list_files = NULL;
	if (fresh[i] == '*' && (i > 0 && fresh[i - 1] == ' ') \
		&& (fresh[i + 1] == '\0' || fresh[i + 1] == ' ') \
		&& (i > 0 && fresh[i - 1] != '\\'))
	{
		left = ft_strsub(fresh, 0, i);
		right = ft_strsub(fresh, i + 1, ft_strlen(fresh));
		list_files = ft_list_file();
		tmp = ft_strjoin(list_files, right);
		final = ft_strjoin(left, tmp);
		ft_free4(tmp, left, right, list_files);
	}
	return (final);
}


/*char * ft_check_files(char *woord)
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
  else if (final != NULL &&										\
  mystrstr(files_tab[j], woord,ft_strlen(woord)) == 0)
  final = ft_add_next_word(found, files_tab[j], final);
  j++;
  }
  ft_free_tab(files_tab);
  return (final);
  }*/

t_msg *ft_star_end(char *fresh, int i, t_msg *final)
{
	char *woord;

	int j;

	j = i;
	woord = NULL;
    if (fresh[i] == '*' && ( i > 0 && fresh[i - 1] != ' ') \
        && (fresh[i + 1] = ' ' || fresh[i + 1] == '\0') \
        && (i == 0 || fresh[i - 1] != '\\'))
	{
		while (i != 0  && fresh[i] != ' ')
			i --;
		woord = ft_strsub(fresh, i+1, j);
//		ft_putchar ('\n');
//		ft_putendl(woord);
		final->str = ft_check_files_end(woord);
		if (final->str == NULL)
            return ((final = ft_error_star_end(final, woord)));
	
//		end = ft_strsub(fresh, + 1, ft_strlen());
	}
	return (final);
}

t_msg *ft_star_before(char * fresh, int i, t_msg *final)
{
	char *woord;
	int i_save;
	char *tmp;
	char * start_cmd;

	start_cmd = NULL;
	tmp = NULL;
	woord = NULL;
	i_save = i + 1;
	if (fresh[i] == '*' && ( i == 0 || fresh[i - 1] == ' ') \
		&& (fresh[i + 1] != ' ') \
		&& (i == 0 || fresh[i - 1] != '\\'))
	{
		start_cmd = ft_strsub(fresh, 0, i);
		while (fresh[i] != ' ' && fresh[i] != '\0')
			i++;
		woord = ft_strsub(fresh, i_save, i);
		final->str = ft_check_files(woord);
		if (final->str == NULL)
			return ((final = ft_error_star(final, woord, start_cmd)));
		tmp = final->str;
		final->str = ft_strjoin(start_cmd, tmp);
		ft_strdel(&tmp);
		ft_strdel(&start_cmd);
		ft_strdel(&woord);
	}
	return (final);
}

int main(int ac, char **av)
{
	char *fresh;
	int i;
	t_msg *final;

	final = NULL;
	final = (t_msg *)malloc(sizeof(t_msg));
	final->str = NULL;
	final->error = 0;
	fresh = NULL;
	if (ac != 2)
		return (-1);
	fresh = ft_strdup(av[1]);


	while (fresh[i] != '\0')
	{
		if (final->error == -1)
			break;
		if ((final->str = ft_star_alone(fresh, i)) != NULL)
		{
			i = 0;
			ft_strdel(&fresh);
			fresh = final->str;
		}
		else if ((final = ft_star_before(fresh, i, final)) != NULL && final->str != NULL)
		{
			i = 0;
			ft_strdel(&fresh);
			fresh = ft_strdup(final->str);
			ft_strdel(&(final->str));
		}
		else if ((final = ft_star_end(fresh, i, final)) != NULL && final->str != NULL)
		{
			i = 0;
			ft_strdel(&fresh);
            fresh = ft_strdup(final->str);
            ft_strdel(&(final->str));
		}
		else
			i++;
	}

	final->str = ft_strdup(fresh);
	ft_strdel(&fresh);
	if (final->str == NULL)
		ft_putendl("final str NULL wtf");
	else
		ft_putendl(final->str);
	ft_strdel(&final->str);
	free(final);

}

//			ft_strdel(&list_files);
//		ft_strdel(&right);
//	ft_strdel(&left);
