#ifndef GLOB2_H
#define GLOB2_H

typedef struct      s_listt
{
    char *str;
    int pos;
    struct s_listt *next;
}                   t_listt;

typedef struct		s_core
{
	char *arg;
	int pos;
	char *directory;
	t_listt *list;
	char prev;
}					t_core;


/* 
** file :: list_utils.c 
** 
*/
t_core *ft_sort_list_del(t_core *core);
t_listt *ft_add_list(t_listt *l, t_listt *l2);
int ft_search_slash(char *s1, int i);
t_listt *init_list(t_listt *list);
t_listt *ft_list_del(t_listt *l1, t_listt *prev);

/* 
** file :: dir_utils.c 
** 
*/
t_listt  *ft_files_to_list(char *directory);
t_listt  *ft_files_to_list_char(char *directory, char c, int pos);

int mystrchr(const char *s, int c);
#endif
