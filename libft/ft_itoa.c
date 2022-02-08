/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 09:05:03 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/08 16:14:38 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	int	find_total_digit(long n)
{
	int	total_digit;

	total_digit = 0;
	if (n == 0)
		total_digit = 1;
	if (n < 0)
		total_digit++;
	while (n != 0)
	{
		total_digit++;
		n /= 10;
	}
	return (total_digit);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	temp_n;
	 int	total_digit;

	temp_n = n;
	total_digit = find_total_digit(temp_n);
	result = (char *)malloc(sizeof(char) * (total_digit + 1));
	if (!(result))
		return (NULL);
	result[total_digit] = '\0';
	if (temp_n == 0)
		result[0] = '0';
	if (temp_n < 0)
	{
		temp_n = temp_n * -1;
		result[0] = '-';
	}
	while (temp_n != 0)
	{
		result[--total_digit] = (temp_n % 10) + '0';
		temp_n /= 10;
	}
	return (result);
}