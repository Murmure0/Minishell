#include "../includes/minishell.h"

extern pid_t g_pid;

/* 
	CTRL + C = SIGINT
	CTRL + \ = SIGQUIT
	CTRL + D = 
*/

void	handle_signal(int sig)
{
	if (sig == SIGINT)
		write(2, "\n", 1);
}