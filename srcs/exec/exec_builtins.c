#include "../../includes/minishell.h"

int	find_builtin(t_node *first_node, t_shell *shell, char exec)
{
	if (first_node[0].cmd)
	{
		if (!ft_strcmp(first_node[0].cmd[0], "echo"))
		{
			if (exec == 'y')
			{
				my_echo(first_node[0].cmd + 1);
				if (first_node->node_nb > 1)
					exit(EXIT_SUCCESS); //on est dans un fork : c'est pour le quitter :)
			}
			return (1);
		}
		if (!ft_strcmp(first_node[0].cmd[0], "cd"))
		{
			if (exec == 'y')
			{
				my_cd(shell, first_node[0].cmd[1]);
				if (first_node->node_nb > 1)
					exit(EXIT_SUCCESS);
			}
			return (1);
		}
		if (!ft_strcmp(first_node[0].cmd[0], "export"))
		{
			if (exec == 'y')
			{
				my_export(shell, first_node[0].cmd);
				if (first_node->node_nb > 1)
					exit(EXIT_SUCCESS);
			}
			return (1);
		}
		if (!ft_strcmp(first_node[0].cmd[0], "unset"))
		{
			if (exec == 'y')
			{
				my_unset(shell, first_node[0].cmd[1]);
				if (first_node->node_nb > 1)
					exit(EXIT_SUCCESS);
			}
			return (1);
		}
		if (!ft_strcmp(first_node[0].cmd[0], "env"))
		{
			if (exec == 'y')
			{
				my_env(shell);
				if (first_node->node_nb > 1)
					exit(EXIT_SUCCESS);
			}
			return (1);
		}
	}
	return (0);
}

void	redir_solo_builtin(t_node *first_node, t_shell *shell, t_exec	*exec_st)
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
	if(exec_st->fd_out != 1)
	{
		oldout = dup(STDOUT_FILENO);
		dup2(exec_st->fd_out, STDOUT_FILENO);
	}
	find_builtin(first_node, shell, 'y');
	if (exec_st->fd_in != 0)
	{
		dup2(oldin, STDIN_FILENO);
		close(oldin);
		close(exec_st->fd_in);
	}
	if (exec_st->fd_out != 1)
	{
		dup2(oldout, STDOUT_FILENO);
		close(oldout);
		close(exec_st->fd_out);
	}
}
