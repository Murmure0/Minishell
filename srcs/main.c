/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:20:01 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/12 14:33:32 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int main(int argc, char **argv, char **env)
{
	t_command lst_cmd;

	init_struct(g_struct); /*fonction qui va initialiser notre structure globale*/
	

	exec(g_struct, lst_cmd);
}
