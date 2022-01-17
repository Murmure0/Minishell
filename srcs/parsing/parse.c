#include "../../includes/minishell.h"

void	parse(t_parsing *parstruct)
{
	check_quotes_for_pipe_split(parstruct);
	parstruct->nodes = ft_split(parstruct->prompt, '|');
	if (!parstruct->nodes)
		ft_exit();
	while (parstruct->nodes && *parstruct->nodes)
	{
		printf("%s\n", *parstruct->nodes);
		parstruct->nodes++;
	}
}