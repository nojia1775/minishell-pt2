/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:06:56 by noah              #+#    #+#             */
/*   Updated: 2024/06/04 13:08:54 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_in_quote(int *in_single, int *in_double, char c)
{
	if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
}