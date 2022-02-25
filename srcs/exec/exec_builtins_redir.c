#include "../../includes/minishell.h"

static void	redir_old_std(int old_std, int fd, int std)
{
	dup2(old_std, std);
	close(old_std);
	close(fd);
}

void	redir_solo_builtin(t_node *first_node, t_shell *shell,
		t_exec	*exec_st)
{
	int	oldin;
	int	oldout;

	oldin = STDIN_FILENO;
	oldout = STDOUT_FILENO;
	if (exec_st->fd_in != 0)
	{
		oldin = dup(STDIN_FILENO);
		dup2(exec_st->fd_in, STDIN_FILENO);
	}
	if (exec_st->fd_out != 1)
	{
		oldout = dup(STDOUT_FILENO);
		dup2(exec_st->fd_out, STDOUT_FILENO);
	}
	find_builtin(first_node, shell, 'y');
	if (exec_st->fd_in != 0)
		redir_old_std(oldin, exec_st->fd_in, STDIN_FILENO);
	if (exec_st->fd_out != 1)
		redir_old_std(oldout, exec_st->fd_out, STDOUT_FILENO);
}
