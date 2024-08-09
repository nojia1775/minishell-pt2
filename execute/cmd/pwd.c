/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:37:37 by almichel          #+#    #+#             */
/*   Updated: 2024/08/09 15:44:35 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//print le pwd
int	print_pwd(char *str, t_data *data)
{
	str = NULL;
	str = getcwd(str, 0);
	printf("%s\n", str);
	free(str);
	data->code = 0;
	return (0);
}
