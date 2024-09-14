/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:37:37 by almichel          #+#    #+#             */
/*   Updated: 2024/09/14 13:06:32 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//print le pwd
int	print_pwd(char *str, t_data *data)
{
	str = NULL;
	str = getcwd(str, 0);
	if (str)
	{
		printf("%s\n", str);
		free(str);
	}
	else
	{
		printf("pwd: error retrieving current directory: getcwd:");
		printf("cannot access parent directories: ");
		printf("No such file or directory\n");
	}
	data->code = 0;
	g_sigint_received = 0;
	return (0);
}
