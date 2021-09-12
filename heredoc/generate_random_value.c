/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_random_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:14:18 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/11 16:14:19 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

char	*generate_random_value(void)
{
	int				fd;	
	unsigned int	randval;
	char			*rand_string;
	char			*r_string;

	fd = open("/dev/random", O_RDONLY);
	read(fd, &randval, sizeof(randval));
	close(fd);
	rand_string = ft_itoa(randval);
	r_string = ft_strjoin("/tmp/heredoc-", rand_string);
	// free(rand_string);
	return (r_string);
}
