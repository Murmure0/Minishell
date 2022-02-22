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

	if (!ft_strncmp(str[0], "-n", 2) && !no_newline(str)) //nonewline = le -nnn est identifié, on ne veut pas l'imprimer, on passe a l'arg suivant
	{
		i++;
		j++;
	}
	while (str[++i]) //on imprime l'arg + espace
	{
		write(1, str[i], ft_strlen(str[i]));
		if (str[++j] != NULL)
			write(1, " ", 1);
	}

	if (!ft_strncmp(str[0], "-n", 2) && !no_newline(str)) //le -nnn est id, on doit faire comme -n et inhiber le \n
	{
		return (0);
	}
	else if ((!ft_strncmp(str[0], "-n", 2) && no_newline(str)) || ft_strncmp(str[0], "-n", 2)) //le -n-nn est id, on doit faie le \n
		write(1, "\n", 1);
	return(0);
}
