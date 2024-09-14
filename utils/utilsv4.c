/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 00:57:46 by almichel          #+#    #+#             */
/*   Updated: 2024/09/14 13:24:48 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_nbr(char *str, char *cmpr)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > ft_strlen(cmpr))
		return (-1);
	while (str[i])
	{
		if (str[i] <= cmpr[i])
			i++;
		else
			return (-1);
	}
	return (0);
}

int	ft_strlen_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (1);
}

int	ft_check_long(char *str)
{
	if (str[0] == '-')
		if (ft_strlen(str) >= ft_strlen("-9223372036854775807"))
			if (check_nbr(str, "-9223372036854775807") == -1)
				return (-1);
	if (str[0] == '+')
		if (ft_strlen(str) >= ft_strlen("+9223372036854775807"))
			if (check_nbr(str, "+9223372036854775807") == -1)
				return (-1);
	if (str[0] != '+' && str[0] != '-')
		if (ft_strlen(str) >= ft_strlen("9223372036854775807"))
			if (check_nbr(str, "9223372036854775807") == -1)
				return (-1);
	return (0);
}
