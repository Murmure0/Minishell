#include "../../includes/minishell.h"

extern int	g_exit_st;

static int	find_echo_cd(t_node *first_node, t_shell *shell, char exec)
{
	if (!ft_strcmp(first_node[0].cmd[0], "echo"))
	{
		if (exec == 'y')
		{
			g_exit_st = my_echo(first_node[0].cmd + 1);
			if (first_node->node_nb > 1)
				exit(EXIT_SUCCESS);
		}
		return (1);
	}
	if (!ft_strcmp(first_node[0].cmd[0], "cd"))
	{
		if (exec == 'y')
		{
			g_exit_st = my_cd(shell, first_node[0].cmd[1]);
			if (first_node->node_nb > 1)
				exit(g_exit_st);
		}
		return (1);
	}
	return (0);
}

static int	find_export_unset(t_node *first_node, t_shell *shell, char exec)
{
	if (!ft_strcmp(first_node[0].cmd[0], "export"))
	{
		if (exec == 'y')
		{
			g_exit_st = my_export(shell, first_node[0].cmd);
			if (first_node->node_nb > 1)
				exit(g_exit_st);
		}
		return (1);
	}
	if (!ft_strcmp(first_node[0].cmd[0], "unset"))
	{
		if (exec == 'y')
		{
			g_exit_st = my_unset(shell, first_node[0].cmd);
			if (first_node->node_nb > 1)
				exit(g_exit_st);
		}
		return (1);
	}
	return (0);
}

static int	find_env_pwd(t_node *first_node, t_shell *shell, char exec)
{
	if (!ft_strcmp(first_node[0].cmd[0], "env"))
	{
		if (exec == 'y')
		{
			g_exit_st = my_env(shell);
			if (first_node->node_nb > 1)
				exit(g_exit_st);
		}
		return (1);
	}
	if (!ft_strcmp(first_node[0].cmd[0], "pwd"))
	{
		if (exec == 'y')
		{
			g_exit_st = my_pwd();
			if (first_node->node_nb > 1)
				exit(g_exit_st);
		}
		return (1);
	}
	return (0);
}

int	find_builtin(t_node *first_node, t_shell *shell, char exec)
{
	if (first_node[0].cmd)
	{
		if (find_echo_cd(first_node, shell, exec))
			return (1);
		if (find_export_unset(first_node, shell, exec))
			return (1);
		if (find_env_pwd(first_node, shell, exec))
			return (1);
		if (!ft_strcmp(first_node[0].cmd[0], "exit"))
		{
			if (exec == 'y')
			{
				my_exit();
				if (first_node->node_nb > 1)
					exit(EXIT_SUCCESS);
			}
			return (1);
		}
	}
	return (0);
}
