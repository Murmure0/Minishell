#include "../../includes/minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

char	*str_slice(char *src, int start, int stop)
{
	char	*string;
	int		src_size;
	int		i;

	if (!src)
		return (NULL);
	src_size = stop - start;
	string = malloc(sizeof(char) * (src_size + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (start < stop)
	{
		string[i] = src[start];
		i++;
		start++;
	}
	string[src_size] = '\0';
	return (string);
}

int	get_files_nb(char *node, char chevron)
{
	int	i;
	int nb;

	i = -1;
	nb = 0;
	while (node && node[++i])
	{
		if (node[i] == chevron)
		{
			while (node[i] && node[i] == chevron)
				i++;
			nb++;
		}
	}
	return (nb);
}

void	skip_spaces(t_parsing *ps)
{
	while (ps->nodes[ps->i][ps->j] && (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' '))
	{
		if (ps->nodes[ps->i][ps->j + 1])
			ps->j++;
	}
}
int	get_cmds_nb(char *node)
{
	int	i;
	int nb;

	i = 0;
	nb = 0;
	while (node && node[i])
	{
		if (node[i] != ' ' && node[i] != '\t' && node[i] != '<' && node[i] != '>')
		{
			while (node[i] && (node[i] != ' ' && node[i] != '\t'))
				i++;
			nb++;
		}
		else if (node[i] == '<' || node[i] == '>')
		{
			if (node[i + 1] && (node[i + 1] == ' ' || node[i + 1] == '\t'))
			{
				i++;
				while (node[i] && (node[i] == '\t' || node[i] == ' '))
					if (node[i + 1])
						i++;
			}
			while (node[i] && (node[i] != ' ' && node[i] != '\t'))
				i++;
		}
		if (node[i] && node[i + 1])
			i++;
		else
			break ;
	}
	return (nb);
}