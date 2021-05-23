/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:53:07 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/18 19:24:20 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		condition(long result, long sign)
{
	if (result > 2147483648 && sign == -1)
		return (0);
	if (result > 2147483647 && sign == 1)
		return (-1);
	return (0);
}

int		ft_atoi(const char *str)
{
	long	sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == 32 || *str == 10 || *str == 9
				|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str < 48 || *str > 57)
			return (result * sign);
		result = (result * 10) + (*str - '0');
		if ((result > 2147483648 && sign == -1)
				|| (result > 2147483647 && sign == 1))
			return (condition(result, sign));
		str++;
	}
	return (result * sign);
}
