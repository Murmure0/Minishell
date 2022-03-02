/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:22:31 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/02 16:37:29 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_st;

void	fd_dup(int fd, int std)
{
	if (dup2(fd, std) < 0)
	{
		close(fd);
		perror(": ");
		if (errno == EBADF)
			exit(9);
		if (errno == EBUSY)
			exit(16);
		if (errno == EINTR)
			exit(4);
		if (errno == EMFILE)
			exit(24);
	}
	close(fd);
}

t_exec	*init_exec_st(t_node *first_node)
{
	t_exec	*exec_st;

	exec_st = malloc(sizeof(t_exec));
	if (!exec_st)
	{
		g_exit_st = -1;
		write(2, "Memory allocation failed.\n", 26);
		return (NULL);
	}
	exec_st->num_cmd = 1;
	exec_st->pfd_in = 0;
	exec_st->pfd_out = 0;
	exec_st->fd_in = find_fd_in(first_node);
	exec_st->fd_out = find_fd_out(first_node, exec_st);
	return (exec_st);
}

static void	exit_err(t_node *first_node)
{
	write(2, "minishell: ", 12);
	write(2, first_node[0].cmd[0], ft_strlen(first_node[0].cmd[0]));
	write(2, ": command not found\n", 21);
	exit(127);
}

int	path_finder(t_node *first_node, t_shell *shell)
{
	char	*cmd;
	int		i;

	i = -1;
	if (first_node[0].cmd[0])
	{
		if (!strcmp(first_node[0].cmd[0], "")
			|| !strcmp(first_node[0].cmd[0], " "))
			exit_err(first_node);
		execve(first_node[0].cmd[0], first_node[0].cmd, shell->env);
		while (shell->path && shell->path[++i])
		{
			cmd = ft_strjoin(shell->path[i], first_node[0].cmd[0]);
			if (!cmd)
				return (-1);
			execve(cmd, first_node[0].cmd, shell->env);
			free(cmd);
		}
		exit_err(first_node);
	}
	else
	{
		g_exit_st = 0;
		exit(0);
	}
	return (0);
}
