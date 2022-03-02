/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:22:43 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/02 13:22:45 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*add_c(char *line, char *new, char c)
{
	size_t	i;

	i = -1;
	while (line[++i])
		new[i] = line[i];
	new[i] = c;
	new[++i] = '\0';
	free(line);
	return (new);
}

static char	*join(char *line, char c)
{
	char	*new;

	if (line)
	{
		new = malloc(sizeof(char) * ft_strlen(line) + 2);
		if (!new)
		{
			free (line);
			return (NULL);
		}
	}
	else
	{
		new = malloc(sizeof(char) * 2);
		if (!new)
			return (NULL);
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	return (add_c(line, new, c));
}

char	*get_next_line(int fd)
{
	char	buff[1];
	char	*line;
	int		ret;

	line = (void *)0;
	if (!read(fd, buff, 1))
		return ((void *)0);
	line = join(line, buff[0]);
	if (!line)
		return ((void *)0);
	while (buff[0] != '\n')
	{
		ret = read(fd, buff, 1);
		if (!ret)
			break ;
		line = join(line, buff[0]);
		if (!line)
			return ((void *)0);
	}
	return (line);
}
