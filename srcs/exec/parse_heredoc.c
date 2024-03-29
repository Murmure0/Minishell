/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:23:01 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/15 09:57:01 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_st;

static void	here_doc_reading(char *line, int pipe_hd, char *del)
{
	while (1)
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			continue ;
		if (!ft_strcmp(line, del))
			break ;
		else
			write(pipe_hd, line, ft_strlen(line));
	}
	free(line);
	free(del);
	close(pipe_hd);
}

static void	in_fork_heredoc(int pipe_in, int pipe_out, char *delimiter)
{
	char	*line;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sig_heredoc);
	line = get_next_line(STDIN_FILENO);
	if (line && !ft_strcmp(line, delimiter))
	{
		free(delimiter);
		free(line);
		close(pipe_in);
		close(pipe_out);
		exit (0);
	}
	else
		write(pipe_out, line, ft_strlen(line));
	here_doc_reading(line, pipe_out, delimiter);
	exit (0);
}

static void	forking_heredoc(int pipe_in, int pipe_out, t_parsing *ps)
{
	pid_t	fork_pid;
	char	*delimiter;

	delimiter = get_delimiter(ps);
	if (!delimiter)
		exit(EXIT_FAILURE);
	fork_pid = fork();
	if (fork_pid < 0)
	{
		g_exit_st = -1;
		free(delimiter);
		close(pipe_in);
		write(2, "Fork failed", 12);
		perror(": ");
	}	
	if (fork_pid != 0)
		signal(SIGINT, SIG_IGN);
	else if (fork_pid == 0)
		in_fork_heredoc(pipe_in, pipe_out, delimiter);
	close(pipe_out);
	free(delimiter);
}

int	parse_case_hd(t_node *nodes, t_parsing *ps)
{
	if (!check_hd_content(ps))
		return (ret_err(0, NO_FILE));
	if (!nodes[ps->i].invalid_infile)
		nodes[ps->i].in_id = 1;
	ps->j++;
	if (add_heredoc_file(nodes, ps))
	{
		ps->stop_err = 1;
		return (0);
	}
	return (1);
}

int	add_heredoc_file(t_node *nodes, t_parsing *ps)
{
	int		pipe_hd[2];
	int		status;

	status = 0;
	if (pipe(pipe_hd) == -1)
	{
		write(2, "Error: pipe failed\n", 19);
		g_exit_st = -1;
		return (1);
	}
	nodes[ps->i].infile_hd = pipe_hd[0];
	forking_heredoc(pipe_hd[0], pipe_hd[1], ps);
	wait(&status);
	if (status != 0)
	{
		g_exit_st = status >> 8;
		return (1);
	}
	return (0);
}
