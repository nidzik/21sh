#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mini.h"



int ft_check_cmd(char *cmd)
{
	struct stat sta;
	int status;
	char **array_cmd;
	int fd;

	if (cmd == NULL)
		return (-1);
	array_cmd = ft_strsplit(ft_strtrim(cmd), ' ');
	ft_putendl(array_cmd[0]);
	fd = open(cmd, O_RDONLY);
	status = fstat(fd, &sta);
	close(fd);
	return status ;
}

int main(int ac, char **av, char **env)
{
	pid_t father;
	char *lines;
	int status;
	char **myenv = env;

	status =  0;
	//	while (1)
	while (get_next_line(0, &lines) > 0)
		{
			if (ft_check_cmd(lines) > 0)
			{
				father = fork();
				if (father > 0)
				{
					wait(&status);
					printf("exec father");
				}
				if (father == 0)
				{
					execve("/bin/ls", NULL, env);
				}
			}		
		}
	//		free(&lines);
		//while(1);
				return (0);
}
