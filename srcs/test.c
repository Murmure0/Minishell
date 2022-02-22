#include "../includes/minishell.h"

int main()
{
	t_node *nodes;
	t_token *tokens;
	char input[50] = "< cat 	>output | ls | echo>out";


	nodes = malloc(sizeof(t_node) * 3);
	int i = -1;
	while (i < 3)
	{
		tokens = malloc(sizeof(t_token) * 100);
		int j = -1;
		while (j < 100)
		{
			tokens[j].name = ;
			nodes[i].infile = 
		
		}
	}
	printf("");
}