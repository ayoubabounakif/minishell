#include "libft.h"

int	rstr_lookup(t_rstr haystack, char *needle)
{
	int	i;
	int j;
	int count;
	
	(void)needle;
	(void)haystack;
	i = 0;
	j = 0;
	count = 0;
	
	while (i < haystack->len)
	{
		j = 0;
		while (j < haystack->len && needle[j])
		{	
			if (((i + j) > haystack->len) || (rstr_get(haystack, i + j) != needle[j]))
				break ;
			if ((size_t)j == (ft_strlen(needle) - 1))		
				return (1);	
			j++;
		}
		i++;
	}
	return (0);
}