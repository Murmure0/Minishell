#include "../../includes/minishell.h"

static char	*adj_av(char *tmp)
{
	char	*str;
	int		len_tmp;
	int		i;

	i = -1;
	len_tmp = ft_strlen(tmp);
	str = malloc(sizeof(char) * len_tmp + 2);
	if (!str)
		return (NULL);
	while (++i < len_tmp)
		str[i] = tmp[i];
	str[len_tmp] = '\n';
	str[len_tmp + 1] = '\0';
	return (str);
}

char	*get_delimiter(t_parsing *ps)
{
	int		pos_start;
	char	*del;
	char	*tmp;

	ps->j++;
	skip_spaces(ps);
	pos_start = ps->j;
	while (ps->nodes[ps->i] && ps->nodes[ps->i][ps->j])
	{
		if (is_space(ps->nodes[ps->i][ps->j]) ||
			is_chevron(ps->nodes[ps->i][ps->j]))
			break ;
		ps->j++;
	}
	tmp = str_slice(ps->nodes[ps->i], pos_start, ps->j);
	// protect
	del = adj_av(tmp);
	// protect
	free(tmp);
	return (del);
}
