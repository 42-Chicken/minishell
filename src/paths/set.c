#include <minishell.h>

char	*get_current_path(t_minishell *data)
{
	char	*path;

	path = (char *)get_env(data->envp, "PWD");
	if (!path)
		path = (char *)data->started_path;
	return (path);
}
