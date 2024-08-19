#include "minishell.h"

int	main(void)
{
	pid_t	pid;
	char	*str;

	str = ft_strdup("test\n");
	pid = fork();
	if (pid == 0)
	{
		free(str);
		sleep(1);
		printf("%s", str);
	}
	else
	{
		waitpid(pid, NULL, 0);
		printf("%s", str);
	}
}