/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:19:02 by aabounak          #+#    #+#             */
/*   Updated: 2019/10/15 20:02:50 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		size;
	int		temp;

	size = 1;
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	if (n < 0 && n != -2147483648)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	temp = n;
	while ((temp /= 10) > 0)
		size *= 10;
	temp = n;
	while (size && n != -2147483648)
	{
		ft_putchar_fd((temp / size) + '0', fd);
		temp %= size;
		size /= 10;
	}
}
