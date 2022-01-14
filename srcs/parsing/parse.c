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

void	check_pipe_split(int next_pipe, int last_pipe)
{
	char	quote;

	if (next_pipe == -1) /* si on a pas de next pipe, pas besoin de checker (juste pour le debut) */
		return ;
	while (g_shell.prompt[++last_pipe] && last_pipe < next_pipe) /* on va du dernier pipe trouvé jusqu au prochain */
	{
		if (g_shell.prompt[last_pipe] == '"' || g_shell.prompt[last_pipe] == '\'')
		{
			quote = g_shell.prompt[last_pipe]; // on save le type de quote
			while (last_pipe < next_pipe && g_shell.prompt[++last_pipe] != quote) // tant quon a pas trouvé le match, on continue
				continue ;
			if (g_shell.prompt[last_pipe] == quote)
				check_pipe_split(ft_strchr_pos(g_shell.prompt, '|', next_pipe), last_pipe); // on relance avec la position du dernier pipe
			else
				ft_exit(); // on a atteint le prochain pipe sans trouver, => erreur
		}
	}
}

void	parse(void)
{
	t_parsing	parstruct;

	/*  - split avec les pipes
		- check gauche et droite des pipes pour trouver " ou '
		- si on trouve, on check sils sont pairs
	*/

	check_pipe_split(ft_strchr_pos(g_shell.prompt, '|', -1), -1);
	parstruct.nodes = ft_split(g_shell.prompt, '|');
	if (!parstruct.nodes)
		ft_exit();
	while (parstruct.nodes && *parstruct.nodes)
	{
		printf("%s\n", *parstruct.nodes);
		parstruct.nodes++;
	}
}