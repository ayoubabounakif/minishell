/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:06:22 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/09 15:49:39 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sign_num)
{
	if (sign_num == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		rl_on_new_line();
		rl_replace_line("", 1); 
		rl_redisplay();
	}
	else if (sign_num == SIGQUIT)
	{
		ft_putchar_fd('\r', 1);
		rl_on_new_line();
		rl_redisplay();
	}
}