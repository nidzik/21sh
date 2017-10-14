#include "../../minishell.h"
#include "glob2.h"

int	mystrchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return (i);
		else
			i++;
		if ((unsigned char)s[i] == (unsigned char)c)
			return (i);
	}
	return (-1);
}
