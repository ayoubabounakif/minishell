#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

unsigned int generate_random_value(void)
{
    int			fd;	
    unsigned	randval;

	fd = open("/dev/random", O_RDONLY);
	read(fd, &randval, sizeof(randval));
	close(fd);
	return (randval);
}

int main(int argc, char **argv)
{ 
    printf("%u\n", generate_random_value());
	printf("%u\n", generate_random_value());
	printf("%u\n", generate_random_value());
	printf("%u\n", generate_random_value());
	printf("%u\n", generate_random_value());
    return (0);
}