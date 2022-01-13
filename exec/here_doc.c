#include "../includes/minishell.h"

/*char	*adj_av(char **av)
{
	char	*str;

	str = malloc(sizeof(char) * my_strlen(av[2]) + 1);
	if (!str)
		return (NULL);
	str = ft_strdup(av[2]);
	str[my_strlen(av[2])] = '\n';
	str[my_strlen(av[2]) + 1] = '\0';
	return (str);
}*/

static void	here_doc_reading(char *line, int fd_hd, char *str)
{
	while (line)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strcmp(line, str))
			break ;
		else
			write(fd_hd, line, my_strlen(line));
	}
	free(line);
	close(fd_hd);
}

static int	is_first_line_limiter(char *line, char *str, int fd_hd)
{
	if (!ft_strcmp(line, str))
	{
		close(fd_hd);
		return (0);
	}
	else
		return (1);
}

int	here_doc(char **av, int ac)
{
	int		fd_hd;
	char	*line;
	char	*str;

	str = adj_av(av); //lst_cmd.infile.name
	if (!ft_strcmp("here_doc", av[1])) // 
	{
		if (ac < 6)
			error_message(10);
		fd_hd = open("/tmp/tmp.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd_hd < 0)
			error_message(2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			error_message(3);
		if (!is_first_line_limiter(line, str, fd_hd))
			return (0);
		else
			write(fd_hd, line, my_strlen(line));
		here_doc_reading(line, fd_hd, str);
		return (0);
	}
	return (1);
}
