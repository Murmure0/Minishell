#include "../includes/minishell.h"

extern int	g_exit_st;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_st = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
		write(1, "\r", 1);
	}
}

void	handle_sig_fork(int sig)
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

void	handle_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
}
