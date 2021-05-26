/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_proccessing.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:32:28 by khafni            #+#    #+#             */
/*   Updated: 2021/05/25 16:27:43 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_PROCCESSING_H
# define QUOTES_PROCCESSING_H
# include "pipelines.h"

char *remove_quotes_from_string(char *a_token);
void process_tokens_from_quotes(t_tokens tks);
#endif