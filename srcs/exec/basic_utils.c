#include "../../includes/minishell.h"


void	ft_lstclear_file(t_file **lst)
{
	t_file	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}

void	ft_lstclear_cmd(t_command **lst)
{
	t_command	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		/*a completer en fonction du contenu de t_command*/
	}
}