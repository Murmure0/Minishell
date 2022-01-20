#include "../../includes/minishell.h"

int find_fd_in(t_node *node)
{
	int fd_in;

	fd_in = 0;
	while (node->infiles->next)
	{
		if (node->infiles->redir == 1)
		{
			fd_in = open(node->infiles->name, O_RDONLY);
			// printf("nom infile : %s\n", node->infiles->name);
			// printf("|%d|\n", fd_in);
			if (fd_in < 0)
			{
				write(2, node->infiles->name, ft_strlen(node->infiles->name));
				perror(": ");
				exit (errno);
			}
			if (node->infiles->next)
			{
				//printf("close %s\n", node->infiles->name);
				close(fd_in);
			}
			node->infiles = node->infiles->next;
		}
	}
	return (fd_in);
}
