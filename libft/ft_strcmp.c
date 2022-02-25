/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 08:48:53 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/24 17:39:54 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while ((*(str1 + i) == *(str2 + i)) && *(str1 + i) != '\0'
		&& *(str2 + i) != '\0')
		i++;
	return ((unsigned char)*(str1 + i) - (unsigned char)*(str2 + i));
}
