# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>

static unsigned long int next = 1;

int ft_rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void ft_srand(unsigned int seed)
{
	next = seed;
}

int	sampleRandNumGen(void)
{
	pid_t	pid = fork();
	int		status;

	if (pid == 0)
		exit(EXIT_SUCCESS);
	ft_srand((unsigned int)&status);
	printf("%d", ft_rand());
	while (waitpid(-1, &status, 0) > 0);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	sampleRandNumGen();
	return (EXIT_SUCCESS);
}