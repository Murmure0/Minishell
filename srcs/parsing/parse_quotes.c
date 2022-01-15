#include "../../includes/minishell.h"

/* renvoit la pos du 1er quote trouvé a partir de la position start, ou -1 sil ne trouve pas */
int		get_quote_pos(int start)
{
	while (g_shell.prompt[++start])
	{
		if (g_shell.prompt[start] == '"' || g_shell.prompt[start] == '\'')
			return (start);
	}
	return (-1);
}

/* renvoit la position du quote qui matche, sinon renvoit 0 (pas possible davoir un matching quote a 0) */
int		get_matching_quote_pos(int start, int quote_pos)
{
	if (quote_pos == -1) //renvoit -1 si on a pas de quote
		return (-1);
	while (g_shell.prompt[++start])
	{
		if (g_shell.prompt[start] == g_shell.prompt[quote_pos])
			return (start);
	}
	return (0); // renvoit 0 si ca matche pas
}

void	check_quotes_for_pipe_split(int next_pipe, int last_pipe)
{
	char	quote;
	int		pos_quote;

	// next_pipe = pos du prochain pipe
	// last_pipe = -1 au debut, puis position du dernier pipe trouvé 
	if (ft_strchr_pos(g_shell.prompt, '|', next_pipe) == -1) /* si on a pas de next pipe, on a besoin de checker les quotes */
	{
		pos_quote = get_matching_quote_pos(next_pipe, get_quote_pos(next_pipe));
		if (pos_quote == -1)
			return ; // si -1, on a pas trouvé de quote donc on peut split
		else if (pos_quote == 0)
			ft_exit(); // si 0 on a trouve un quote qui ne matche pas
	}
	while (g_shell.prompt[++last_pipe] && last_pipe < next_pipe) /* on va du dernier pipe trouvé jusqu au prochain */
	{
		if (g_shell.prompt[last_pipe] == '"' || g_shell.prompt[last_pipe] == '\'')
		{
			quote = g_shell.prompt[last_pipe]; // on save le type de quote
			while (last_pipe < next_pipe && g_shell.prompt[++last_pipe] != quote) // tant quon a pas trouvé le match, on continue
				continue ;
			if (g_shell.prompt[last_pipe] == quote && ft_strchr_pos(g_shell.prompt, '|', next_pipe) != -1)
				check_quotes_for_pipe_split(ft_strchr_pos(g_shell.prompt, '|', next_pipe), last_pipe); // on relance avec la position du dernier pipe
			else if (g_shell.prompt[last_pipe] == quote && ft_strchr_pos(g_shell.prompt, '|', next_pipe) == -1)
				break ; // on a trouve le quote et il ny a plus de pipes apres => checker si il y a dautres quotes ??
			else
				ft_exit(); // on a atteint le prochain pipe sans trouver, => erreur
		}
	}
}
