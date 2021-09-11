/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 08:07:28 by khafni            #+#    #+#             */
/*   Updated: 2021/09/11 14:14:57 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_if_after_last_pipe(char *mask, t_syx_check syx)
{
	int	i;
	int	is_pipe;

	i = 0;
	is_pipe = 0;
	while (mask[i])
	{
		if ((is_pipe) && (mask[i] != '|') && mask[i] != 'W')
			is_pipe = 0;
		if (is_pipe && mask[i] == '|')
			syntax_set_error(syx, "error around the pipe");
		else if (!is_pipe && mask[i] == '|')
			is_pipe = 1;
		i++;
	}
}

void	check_pipes_n_semiclns(char *parsing_line, t_syx_check syx)
{
	int		i;
	int		is_pipe;
	char	*mask;

	mask = get_mask(parsing_line);
	i = 0;
	is_pipe = 0;
	check_if_between_pipes_is_empty(mask, syx);
	check_if_after_last_pipe(mask, syx);
	if (mask[0] == '|')
		syntax_set_error(syx, "parse error around the pipe");
	while (mask[i])
	{
		if ((is_pipe) && (mask[i] != '|'))
			is_pipe = 0;
		if (is_pipe && mask[i] == '|')
			syntax_set_error(syx, "error around the pipe");
		else if (!is_pipe && mask[i] == '|')
			is_pipe = 1;
		if (ft_strlen(parsing_line) >= 1
			&& (mask[ft_strlen(parsing_line) - 1] == '|'))
			syntax_set_error(syx, "error around the pipe or semicolon");
		i++;
	}
	free(mask);
}

int	check_if_not_redir_sign(char *mask)
{
	if (ft_strnstr(mask, ">>>", ft_strlen(mask))
		|| ft_strnstr(mask, "<<<", ft_strlen(mask))
		|| ft_strnstr(mask, "<>", ft_strlen(mask))
		|| ft_strnstr(mask, "><", ft_strlen(mask)))
		return (1);
	return (0);
}

int	is_betweenRedirSings_space(char *mask)
{
	t_rstr	rs;
	int		i;

	rs = rstr_create(0);
	i = 0;
	while (mask[i])
	{
		if (mask[i] != 'W')
			rstr_add(rs, mask[i]);
		i++;
	}
	if (rstr_lookup(rs, ">>>")
		|| rstr_lookup(rs, "<<<")
		|| rstr_lookup(rs, "<>")
		|| rstr_lookup(rs, "><")
		|| rstr_lookup(rs, ">|")
		|| rstr_lookup(rs, "<|")
		|| (rstr_get(rs, rs->len - 1) == '>')
		|| (rstr_get(rs, rs->len - 1) == '<'))
	{	
		rstr_destroy(rs);
		return (1);
	}	
	rstr_destroy(rs);
	return (0);
}

void	check_redir_syntax(char *parsing_line, t_syx_check syx)
{
	int		i;
	char	*mask;

	mask = get_mask(parsing_line);
	i = 0;
	if (check_if_not_redir_sign(mask))
		syntax_set_error(syx, "error around redirection sign");
	if (is_betweenRedirSings_space(mask))
		syntax_set_error(syx, "error around redirection sign!");
	free(mask);
}