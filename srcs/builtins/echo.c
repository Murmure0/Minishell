#include "../../includes/minishell.h"

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

int	my_echo(char **str)
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
