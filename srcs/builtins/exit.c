/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:26:18 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/07 17:32:38 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_nb_arg(t_node *first_node)
{
	if (first_node->cmd[2] != NULL)
	{
		write(2, "exit\n", 5);
		write(2, "minishell: exit : too many arguments\n", 37);
		rl_on_new_line();
		return (0);
	}
	return (1);
}

int	isnum(int n)
{
	if (n < '0' || n > '9')
		return (0);
	return (1);
}

static int	check_type_arg(t_node *first_node)
{
	int	i;

	i = -1;
	if (first_node->cmd[1][0] == '-')
		i++;
	while (first_node->cmd[1][++i])
	{
		if (!isnum(first_node->cmd[1][i]))
		{
			write(2, "exit\n", 5);
			write(2, "minishell: exit: ", 18);
			write(2, first_node->cmd[1], ft_strlen(first_node->cmd[i]));
			write(2, ": numeric argument required\n", 29);
			rl_on_new_line();
			return (0);
		}
	}
	return (1);
}

int	my_exit(t_node *first_node)
{
	int	n_exit;

	n_exit = 0;
	if (first_node->cmd[1])
	{
		if (!check_type_arg(first_node))
			exit (2);
		else if (!check_nb_arg(first_node))
			return (0);
		if (ft_atoi(first_node->cmd[1]) == -1
			|| ft_atoi(first_node->cmd[1]) == -0)
			n_exit = 0;
		else
			n_exit = (ft_atoi(first_node->cmd[1]) & 0xFF);
	}
	write(1, "exit\n", 5);
	exit(n_exit);
}
