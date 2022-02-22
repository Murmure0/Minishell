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

static char *get_delimiter(t_parsing *ps)
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
	del = adj_av(tmp);
	free(tmp);
	return (del);
}

static void	here_doc_reading(char *line, int pipe_hd, char *del)
{
	while (line)
	{
		//free(line);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strcmp(line, del))
			break ;
		else
			write(pipe_hd, line, ft_strlen(line));
	}
	free(line);
	free(del);
	close(pipe_hd);
}

int	add_heredoc_file(t_node *nodes, t_parsing *ps)
{

	int		pipe_hd[2];
	char	*delimiter;
	char	*line;

	if (pipe(pipe_hd) == -1)
	{
		write(2, "Error: pipe failed\n", 19);
		//free_cmds_path(script, path_env);
		//exit(1);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sig_heredoc);
	nodes[ps->i].infile_hd = pipe_hd[0];
	delimiter = get_delimiter(ps);
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (ret_err(0, NULL));
	if (!ft_strcmp(line, delimiter))
	{
		free(delimiter);
		free(line);
		close(pipe_hd[0]);
		close(pipe_hd[1]);
		return (0);
	}
	else
		write(pipe_hd[1], line, ft_strlen(line));
	here_doc_reading(line, pipe_hd[1], delimiter);
	return (0);
}


/*
static void	here_doc_reading(char *line, int fd_hd, char *del)
{
	while (line)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strcmp(line, del))
			break ;
		else
			write(fd_hd, line, ft_strlen(line));
	}
	free(line);
	free(del);
	close(fd_hd);
}

static int	add_hd_infile(t_node *nodes, t_parsing *ps, char add_infile)
{
	int fd_hd;
	char *delimiter;
	char *line;

	delimiter = get_delimiter(ps);
	fd_hd = open("/tmp/tmp.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (!fd_hd)
		return (ret_err(0, NULL));
	if (add_infile == 'y')
	{
		printf("addinfile EOF\n");
		nodes[ps->i].infiles = ft_strdup("/tmp/tmp.txt");
	}
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (ret_err(0, NULL));
	printf("Line is : |%s|\n", line);
	printf("return strcmp : %d\n", ft_strcmp(line, delimiter));
	if (!ft_strcmp(line, delimiter))
	{
		free(delimiter);
		free(line);
		close(fd_hd);
		return (0);
	}
	else
		write(fd_hd, line, ft_strlen(line));
	here_doc_reading(line, fd_hd, delimiter);
	return (0);
}

int	add_heredoc_file(t_node *nodes, t_parsing *ps)
{
	if (!nodes->invalid_infile)
		add_hd_infile(nodes, ps,'y');
	else if (nodes->invalid_infile)
		add_hd_infile(nodes, ps,'n');
	return (1);
}*/