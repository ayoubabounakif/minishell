#include "libft.h"

int	rstr_lookup(t_rstr haystack, char *needle)
{
	int	i;
	int j;	
	
	(void)needle;
	(void)haystack;
	i = 0;
	j = 0;	
	
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

int	cstr_lookup(char *haystack, char *needle)
{
	t_rstr	rs;
	int		i;
	
	rs = cstr_to_rstr(haystack);
	i = rstr_lookup(rs, needle);
	rstr_destroy(rs);
	return (i);
}