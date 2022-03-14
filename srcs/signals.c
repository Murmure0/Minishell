/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelle <maelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:55:52 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/14 17:27:39 by maelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_st;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(2, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_st = 1;
	}
	else if (sig == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
		rl_on_new_line();
		write(2, "\r", 1);
	}
}

void	handle_sig_fork(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
	}
	else if (sig == SIGQUIT)
	{
		write(2, "Quit: 3\n", 9);
		rl_on_new_line();
		write(2, "\r", 1);
	}
}

void	handle_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		exit(130);
	}
}
