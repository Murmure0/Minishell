#include "../includes/minishell.h"

extern pid_t g_pid;

/* 
	CTRL + C = SIGINT
	CTRL + \ = SIGQUIT
	CTRL + D = 

*/

void	handle_signal(int sig)
{
	printf("%d\n", sig);
	printf("signal detected !\n");
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		printf("SIGINT !\n");
	}
}