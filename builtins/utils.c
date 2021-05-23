/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:40:48 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/06 12:40:49 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_in_out(int in, int out)
{
	if (in != STDIN)
	{
		dup2(in, STDIN);
		close(in);
	}
	if (out != STDOUT)
	{
		dup2(out, STDOUT);
		close(out);
	}
}
