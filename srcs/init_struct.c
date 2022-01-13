#include "../includes/minishell.h"

void    init_struct(t_shell *g_struct, char **env)
{
    g_struct->env = get_env(env);
    g_struct->path = get_env_paths(env);
}