/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelle <maelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 08:48:53 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/20 14:32:48 by maelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] || s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	return (0);
// }

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while ((*(str1 + i) == *(str2 + i)) && *(str1 + i) != '\0'
		&& *(str2 + i) != '\0')
		i++;
	return ((unsigned char)*(str1 + i) - (unsigned char)*(str2 + i));
}