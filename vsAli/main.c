# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>

# include "mtwister/mtwister.h"

static unsigned long int next = 1;

int	zbi = 0;

int ft_rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void ft_srand(unsigned int seed)
{
	next = seed;
}

int	_main_(void)
{
	pid_t	pid = fork();
	int		status;

	if (pid == 0)
		exit(420);
	ft_srand((unsigned int)&status);
	zbi = ft_rand();
	while (waitpid(-1, &status, 0) > 0);
	return 0;
}

int	main(void)
{
	_main_();
	return (zbi);
}