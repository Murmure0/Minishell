/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:26:10 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/25 19:25:09 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	my_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
