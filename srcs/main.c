/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 06:59:26 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/02 07:48:50 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_st;

static void	add_spaces(t_parsing *ps)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strdup(ps->prompt);
	if (!tmp)
		exit(EXIT_FAILURE);
	free(ps->prompt);
	ps->prompt = malloc(sizeof(char) * ft_strlen(tmp) + 3);
	if (!ps->prompt)
		exit(EXIT_FAILURE);
	ps->prompt[0] = ' ';
	while (tmp && tmp[++i])
	{
		ps->prompt[i + 1] = tmp[i];
	}
	free(tmp);
	ps->prompt[i + 1] = ' ';
	ps->prompt[i + 2] = 0;
}

static void	custom_add_history(t_parsing *ps)
{
	char	*tmp;

	tmp = str_slice(ps->prompt, 1, ft_strlen(ps->prompt) - 1);
	if (!tmp)
		exit(EXIT_FAILURE);
	add_history(tmp);
	free(tmp);
}

static void	process_readline(t_parsing *ps, t_node *nodes, t_shell *shell)
{
	custom_add_history(ps);
	if (not_emptycmd(ps->prompt))
	{
		if (!init_global_struct(ps, shell))
			return ;
		nodes = parse(ps, shell);
		if (ps->stop_err)
		{
			final_free(NULL, ps, nodes);
			return ;
		}
		free_parstruct(ps);
		if (nodes)
		{
			exec(nodes, shell);
			free_nodestruct(nodes);
		}
	}
	else
	{
		free(ps->prompt);
		ps->prompt = NULL;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_parsing	parstruct;
	t_node		*nodes;
	t_shell		shell;

	(void)argc;
	(void)argv;
	nodes = NULL;
	g_exit_st = 0;
	init_shell_struct(&shell, env);
	tcgetattr(STDIN_FILENO, &shell.termios_p);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_signal);
		parstruct.prompt = readline("minishell$ ");
		if (!parstruct.prompt)
		{
			write(1, "exit\n", 5);
			break ;
		}
		add_spaces(&parstruct);
		process_readline(&parstruct, nodes, &shell);
	}
	free_shellstruct(&shell);
	return (g_exit_st);
}
