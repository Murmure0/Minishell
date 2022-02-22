#include "../includes/libft.h"

static	int	count_elems(char const *s, char c)
{
	int	i;
	int	nb_elems;

	nb_elems = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			nb_elems++;
		i++;
	}
	return (nb_elems);
}

static	int	count_elem_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static	char	**free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

void	process_fill_arr_first()
{
	while (s[i] && (s[i] != c || is_quote))
	{
		set_quote(s[i], &is_quote);
		arr[j][k++] = s[i++];
	}
	arr[j++][k] = '\0';
}

void	process_fill_arr_second()
{

}

static	char	**fill_arr(char const *s, char **arr, char c, int is_quote)
{
	int	i;
	int	j;
	int	k;
	int	elem_len;

	i = 0;
	j = 0;
	while (s[i])
	{
		set_quote(s[i], &is_quote);
		if (s[i] != c)
		{
			k = 0;
			elem_len = count_elem_len(s, c, i);
			process_fill_arr_first();
			arr[j] = (char *)malloc((elem_len + 1) * sizeof(char));
			if (!arr[j])
				return (free_arr(arr));
			while (s[i] && (s[i] != c || is_quote))
			{
				set_quote(s[i], &is_quote);
				arr[j][k++] = s[i++];
			}
			arr[j++][k] = '\0';
			if (!s[i])
				return (arr);
		}
		i++;
	}
	return (arr);
}

char	**ft_split_pipe(char const *s, char c)
{
	char	**arr;
	int		nb_elems;
	int		is_quote;

	if (!s)
		return (NULL);
	is_quote = 0;
	nb_elems = count_elems(s, c);
	arr = (char **)malloc((nb_elems + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[nb_elems] = 0;
	arr = fill_arr(s, arr, c, is_quote);
	return (arr);
}
