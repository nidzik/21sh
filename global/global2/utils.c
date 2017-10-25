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
	}
	return (-1);
}

int	mystrchrfrom(const char *s, int c, int from)
{
	int i;

	if (from > ft_strlen(s))
		return (-1);
	i = from;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return (i);
		else
			i++;
	}
	return (-1);
}
