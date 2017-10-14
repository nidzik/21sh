#ifndef GLOB_H
#define GLOB_H

typedef struct		s_msg
{
	char 			*str;
	int				error;
}					t_msg;

int					mystrstr(char * s1, char *s2, int c);
char				*ft_list_file(void);
char				**ft_list_file_check(void);
int					nb_files_in_dir(void);

/*
** utils_glob.c
*/
char 				*ft_add_next_word(char *found, char *files_tab, \
										char *final);
void				ft_free4(char *s1, char *s2, char *s3, char *s4);
void				ft_free_tab(char **arr);

/*
** error.c
*/
t_msg				*ft_error_star(t_msg *final, char *woord, char *start);
t_msg				*ft_error_star_end(t_msg *final, char *woord);

/*
** error.c
*/
char				*ft_check_files(char *woord);
char				*ft_check_files_end(char *woord);

#endif
