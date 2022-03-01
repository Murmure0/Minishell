/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:33:36 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/01 13:36:10 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_st;

void	init_shell_struct(t_shell *shell, char **env)
{
	shell->env = get_env(env);
	if (!shell->env)
		ft_exit(shell, NULL, NULL, "Fail to get env in init_shell_struct\n");
	shell->path = get_env_paths(env);
	if (!shell->path)
		ft_exit(shell, NULL, NULL, "Fail to get path in init_shell_struct\n");
}

int	init_global_struct(t_parsing *ps, t_shell *sh)
{
	ps->stop_err = 0;
	ps->is_s_quote = 0;
	ps->is_d_quote = 0;
	ps->quote = 0;
	ps->i = -1;
	ps->k = 0;
	ps->nodes = NULL;
	ps->pipe_nb = 0;
	if (!check_quotes_for_pipe_split(ps))
		return (0);
	ps->nodes = ft_split_pipe(ps->prompt, '|', ps);
	if (!ps->nodes) 
		ft_exit(sh, ps, NULL, "Fail to split nodes in init_global_struct\n");
	while (++(ps->i) <= ps->pipe_nb)
	{
		if (!ps->nodes[ps->i] || (is_space(ps->nodes[ps->i][0]) && !ps->nodes[ps->i][1]))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			g_exit_st = 258;
			return (0);
		}
	}
	ps->pipe_nb = arr_len(ps->nodes) - 1;
	ps->i = 0;
	return (1);
}

void	init_nodestruct(t_node **nodes, t_parsing **ps, t_shell *sh)
{
	(*nodes)[(*ps)->i].node_nb = (*ps)->pipe_nb + 1;
	(*nodes)[(*ps)->i].infiles = 0;
	(*nodes)[(*ps)->i].infile_hd = 0;
	(*nodes)[(*ps)->i].in_id = 0;
	(*nodes)[(*ps)->i].outfiles = 0;
	(*nodes)[(*ps)->i].append = 0;
	(*nodes)[(*ps)->i].invalid_infile = 0;
	(*nodes)[(*ps)->i].cmd = malloc(sizeof(char *) * ((*ps)->cmd_nb + 1));
	if (!(*nodes)[(*ps)->i].cmd)
		ft_exit(sh, *ps, *nodes,
			"Fail to malloc nodes cmds in init_shell_struct\n");
	(*nodes)[(*ps)->i].cmd[(*ps)->cmd_nb] = 0;
}

void	init_local_struct(t_node **nodes, t_parsing **ps, t_shell *sh)
{
	char	*tmp;

	(*ps)->pos_cmd = 0;
	(*ps)->pos_tmp = 0;
	(*ps)->j = 0;
	tmp = ft_strtrim((*ps)->nodes[(*ps)->i], " ");
	free((*ps)->nodes[(*ps)->i]);
	(*ps)->nodes[(*ps)->i] = ft_strdup(tmp);
	free(tmp);
	if (!(*ps)->nodes[(*ps)->i])
		ft_exit(sh, *ps, *nodes, "Fail to trim in init_local_struct\n");
	tmp = ft_strtrim((*ps)->nodes[(*ps)->i], "\t");
	free((*ps)->nodes[(*ps)->i]);
	(*ps)->nodes[(*ps)->i] = ft_strdup(tmp);
	free(tmp);
	if (!(*ps)->nodes[(*ps)->i])
		ft_exit(sh, *ps, *nodes, "Fail to trim in init_local_struct\n");
	(*ps)->cmd_nb = get_cmds_nb((*ps), (*ps)->nodes[(*ps)->i]);
	init_nodestruct(nodes, ps, sh);
}
