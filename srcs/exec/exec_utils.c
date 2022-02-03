#include "../../includes/minishell.h"

int	path_finder(t_node *first_node, t_shell shell)
{
	char	*tmp;
	int		i;

	tmp = first_node[0].cmd[0];
	i = -1;
	while (shell.path[++i])
	{
		first_node[0].cmd[0] = ft_strjoin(shell.path[i], tmp);
		if (!tmp)
			return (-1);
		execve(first_node[0].cmd[0], first_node->cmd, shell.env);
		free(first_node[0].cmd[0]);
	}
	first_node[0].cmd[0] = tmp;
	execve(first_node->cmd[0], first_node->cmd, shell.env);
	return (0);
}

// char **built_array_builtin(void)
// {
// 	char **array_builtin;

// 	array_builtin = malloc(sizeof(char *) * 2);
// 	array_builtin[1] = NULL;
// 	array_builtin[0] = "echo";
// 	return (array_builtin);
// }

int find_builtin(t_node *first_node)
{
	 //int i = -1;
	// char **array_builtin;

	// array_builtin = built_array_builtin();
	// while (array_builtin[++i])
	// {

	if (!ft_strncmp(first_node[0].cmd[0], "echo", ft_strlen(first_node[0].cmd[0])))
	{
			my_echo(first_node[0].cmd + 1);
			return(1);
	}

	return (0);
}

int	exec_cmd(t_node *first_node, t_shell shell)
{
	// if (!find_builtin(first_node))
	// {
	//printf("Contenu de cmd : %s",(first_node[0].cmd[0] + 1));
	if (!path_finder(first_node, shell))
	{
		//free_all(first_node); faire une bonne fct free
		return (-1);
	}
	//}
	return (0);
}

/*
void	free_all(t_node *first_node, t_shell shell)
{
	int i = -1;
	while (shell.env[++i])
		free(shell.env[i]);
	i = -1;
	while (shell.path[++i])
		free(shell.path[i]);
	free(shell.env);
	free(shell.path);
	
	i = -1;
	while(first_node[0].cmd[++i])
		free(first_node[0].cmd[i]);
	i = -1;
	while(first_node[0].infiles[++i])
		free(first_node[0].infiles[i]);
	i = -1;
	while(first_node[0].outfiles[++i])
		free(first_node[0].outfiles[i]);
		doit on free egalement les champs name ?
}*/