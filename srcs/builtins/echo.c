//#include "../../includes/minishell.h"
#include <stddef.h>
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
/*
int newline(char **str)
{
	while (str[0])
	{
		if (!ft_strncmp(str[0], "-n", 2)) //si on a le premier arg qui est -n
			while(str[0])
	}
}*/

int echo(char **str)
{
	int i;
	int j;
	int k;

	i = -1;
	j = 0;
	k = 0;
	if (!str)
		return (-1);

	/*
	while (str[0][++i])
	{
		if (ft_strncmp(str[0][i], "n", 1))
			k = 1;
	}
	i = -1;*/
	if (!ft_strncmp(str[0], "-n", ft_strlen(str[0])))
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
	if (ft_strncmp(str[0], "-n", ft_strlen(str[0])))
		write(1, "\n", 1);
	return(0);
}

int main()
{
	char *str[4] = {"-n", "hello", "bla", NULL};
	char *str2[4] = {"BONJOUR", "CA", "VA", NULL};
	char *str3[3] = {"Bof", "bif", NULL};
	// printf("longueur de la str : |%zu|", ft_strlen(str[1]));
	// write(1, str[1], ft_strlen(str[1]));
	echo(str);
	echo(str2);
	echo(str3);
	return(0);
}

