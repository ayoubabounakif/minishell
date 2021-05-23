/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:04:44 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 19:31:21 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	while (*(char*)s != '\0' && *s != (char)c)
		s++;
	if (*(char*)s == (char)c)
		return ((char*)s);
	return (0);
}

int	output(char **line, char **s, int k)
{
	char		*str;
	int			indicator;

	indicator = 1;
	if (k < 0)
		return (-1);
	if (!(str = ft_strchr(*s, '\n')))
	{
		str = ft_strchr(*s, '\0');
		indicator = 0;
	}
	str++;
	if (!(*line = malloc(sizeof(char) * (str - *s) + 1)))
		return (-1);
	ft_strlcpy(*line, *s, (str - *s));
	str = *s;
	*s = ft_substr(*s, ft_strlen(*line) + 1,
			ft_strlen(*s) - ft_strlen(*line) + 1);
	free(str);
	if ((indicator == 0) || *line)
	{
		s = 0;
		return ((indicator == 0) ? 0 : 1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char		*s;
	char			*buffer;
	char			*temp;
	int				k;

	if (BUFFER_SIZE < 0 || fd < 0 || line == NULL)
		return (-1);
	if (!(buffer = malloc(BUFFER_SIZE + 1)))
		return (-1);
	if (s == NULL)
		s = ft_strdup("");
	while (!ft_strchr(s, '\n') && (k = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[k] = '\0';
		temp = s;
		s = ft_strjoinn(s, buffer);
		free(temp);
	}
	free(buffer);
	return (output(line, &s, k));
}
