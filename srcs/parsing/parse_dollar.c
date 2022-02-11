#include "../../includes/minishell.h"

int	contains_dollar(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '$')
			return (i);
	}
	return (-1);
}