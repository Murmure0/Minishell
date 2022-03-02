/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 07:03:08 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/02 07:04:22 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ret_err(int ret, char *msg)
{
	if (!msg)
		perror(PERR);
	else
		printf("%s\n", msg);
	return (ret);
}

void	ft_exit(t_shell *sh, t_parsing *ps, t_node *n, char *err)
{
	(void)sh;
	(void)ps;
	(void)n;
	if (err)
		write(2, err, ft_strlen(err));
	exit(EXIT_FAILURE);
}

int	not_emptycmd(char *cmd)
{
	int	i;

	i = -1;
	if (cmd == NULL)
		return (1);
	while (cmd[++i])
	{
		if (!is_space(cmd[i]))
			return (1);
	}
	return (0);
}
