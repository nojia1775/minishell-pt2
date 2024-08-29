/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_lobby2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 02:05:24 by almichel          #+#    #+#             */
/*   Updated: 2024/08/28 21:14:49 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_total_setup(t_data *data)
{
	int	len;

	len = ft_strlen(data->logname) + ft_strlen(data->extract_pwd);
	len = len + ft_strlen(" \u27a4 ") + 1;
	data->total_setup = malloc((len) * sizeof(char));
	if (!data->total_setup)
		return (NULL);
	data->total_setup = ft_str3cat(data->logname,
			data->extract_pwd, " \u27a4 ", data->total_setup);
	free(data->logname);
	free(data->extract_pwd);
	return (data->total_setup);
}
