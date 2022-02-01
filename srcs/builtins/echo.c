#include "../../includes/minishell.h"
/*
#include <unistd.h>
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

size_t ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return(-1);
	while (str[i])
		i++;
	return (i);
}
*/

int no_newline(char **str)
{
	int	k;

	k = 2;
	while (str[0][k] == 'n')
		k++;
	if (k == ft_strlen(str[0]))
		return (0);
	else
		return (1);
}

int	echo(char **str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (!str || !*str)
	{
		write(1, "\n", 1);
		return (-1);
	}
	if (!ft_strncmp(str[0], "-n", 2) && !no_newline(str))
	{
		i++;
		j++;
	}
	while (str[++i])
	{
		write(1, str[i], ft_strlen(str[i]));
		if (str[++j] != NULL)
			write(1, " ", 1);
	}
	if (!ft_strncmp(str[0], "-n", 2) && !no_newline(str))
		write(1, "\n", 1);
	else if (ft_strncmp(str[0], "-n", 2))
		write(1, "\n", 1);
	return(0);
}

/*
int main()
{
	char *str[4] = {"         ", NULL};
	char *str2[4] = {"-n-nnnn", "CA", "VA", NULL};
	char *str3[3] = {"-nnnnnnnn", "bif", NULL};
	char*str4[3] = {"debut", "str4", NULL};
	echo(str);
	echo(str2);
	echo(str3);
	echo(str4);
	echo(str4);
	return(0);
}
*/
