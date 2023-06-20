#include "libft/libft.h"
#include "env.h"

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}

