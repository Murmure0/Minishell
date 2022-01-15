#include "../../includes/minishell.h"

int	arr_len(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

// int	get_quotes_nb(char c)
// {
// 	int	i;
// 	int	quotes_nb;

// 	i = -1;
// 	quotes_nb = 0;
// 	while (g_shell.prompt[++i])
// 	{
// 		if (g_shell.prompt[i] == c)
// 			quotes_nb++;
// 	}
// 	return (quotes_nb);
// }

void	parse(void)
{
	t_parsing	parstruct;

	/*  - split avec les pipes
		- check gauche et droite des pipes pour trouver " ou '
		- si on trouve, on check sils sont pairs
	*/

	check_quotes_for_pipe_split(ft_strchr_pos(g_shell.prompt, '|', -1), -1);
	parstruct.nodes = ft_split(g_shell.prompt, '|');
	if (!parstruct.nodes)
		ft_exit();
	while (parstruct.nodes && *parstruct.nodes)
	{
		printf("%s\n", *parstruct.nodes);
		parstruct.nodes++;
	}
}