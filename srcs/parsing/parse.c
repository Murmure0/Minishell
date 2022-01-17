#include "../../includes/minishell.h"

void	parse(void)
{
	t_parsing	parstruct;

	check_quotes_for_pipe_split();
	parstruct.nodes = ft_split(g_shell.prompt, '|');
	if (!parstruct.nodes)
		ft_exit();
	while (parstruct.nodes && *parstruct.nodes)
	{
		printf("%s\n", *parstruct.nodes);
		parstruct.nodes++;
	}
}