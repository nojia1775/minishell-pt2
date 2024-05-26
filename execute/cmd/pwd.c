/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:37:37 by almichel          #+#    #+#             */
/*   Updated: 2024/05/26 03:49:44 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//print le pwd
int	print_pwd(char *str, t_data *data)
{
				str = NULL;
				str = getcwd(str, 0);
				ft_printf("%s\n", str);
				free(str);
				data->code = 0;
				return (0);
}
