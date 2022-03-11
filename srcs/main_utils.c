/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:28:10 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/11 16:31:25 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_readline_inside(t_parsing *ps, t_node *nodes, t_shell *shell)
{
	if (nodes)
	{
		if (ps->cmd_nb)
			exec(nodes, shell);
		free_nodestruct(nodes, NULL);
	}
}
