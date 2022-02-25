#include "../../includes/minishell.h"

static int	redir_old_std(int old_std, int fd, int std)
{
	if (dup2(old_std, std) < 0)
	{
		close(old_std);
		perror(": ");
		g_exit_st = -1;
		return (g_exit_st);
	}
	close(old_std);
	close(fd);
	return (0);
}

static int	redir_new_std(int new_std, int std)
{
	if (dup2(new_std, std) < 0)
	{
		close(new_std);
		perror(": ");
		g_exit_st = -1;
		return (g_exit_st);
	}
	return (0);
}

int	redir_solo_builtin(t_node *first_node, t_shell *shell,
		t_exec	*exec_st)
{
	int	oldin;
	int	oldout;

	oldin = STDIN_FILENO;
	oldout = STDOUT_FILENO;
	if (exec_st->fd_in != 0)
	{
		oldin = dup(STDIN_FILENO);
		if (redir_new_std(exec_st->fd_in, STDIN_FILENO) < 0)
			return(g_exit_st);
	}
	if (exec_st->fd_out != 1)
	{
		oldout = dup(STDOUT_FILENO);
		if (redir_new_std(exec_st->fd_out, STDOUT_FILENO) < 0)
			return(g_exit_st);
	}
	find_builtin(first_node, shell, 'y');
	if (exec_st->fd_in != 0)
		if (redir_old_std(oldin, exec_st->fd_in, STDIN_FILENO) < 0)
			return(g_exit_st);
	if (exec_st->fd_out != 1)
		if (redir_old_std(oldout, exec_st->fd_out, STDOUT_FILENO) < 0)
			return (g_exit_st);
	return (0);
}
