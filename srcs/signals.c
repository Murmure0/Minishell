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
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
		write(1, "\r", 1);
	}
}

void handle_sig_fork(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 9);
		rl_on_new_line();
		write(1, "\r", 1);
	}
}

void handle_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\x03", 2);
		// exit(130);
	}
}