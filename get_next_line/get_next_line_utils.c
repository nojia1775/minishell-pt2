/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:07:47 by almichel          #+#    #+#             */
/*   Updated: 2024/05/16 17:37:28 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str, int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
	{
		while (str[i])
			i++;
	}
	if (nb == 1)
	{
		while (str[i] && str[i] != '\n')
			i++;
	}
	return (i);
}

void	ft_avoid_crushing(char *buf, char *line)
{
	int	i;

	i = -1;
	while (buf[++i] && buf[i] != '\n')
		line[i] = buf[i];
	line[i] = '\0';
}

void	ft_check_n_fractionned(char *str, char *dest, int nb)
{
	int	i;

	i = -1;
	if (nb == 0)
	{
		while (str[++i])
			dest[i] = str[i];
		dest[i] = '\0';
	}
	if (nb == 1)
	{
		while (str[++i] != '\n')
			dest[i] = str[i];
		dest[i] = '\n';
		dest[++i] = '\0';
	}
}

char	*ft_check_n(char *str, int *error)
{
	char	*dest;

	if (found_newline(str) == 0)
	{
		dest = malloc((ft_strlen_gnl(str, 0) + 1) * sizeof(char));
		if (!dest)
		{
			*error = 1;
			return (NULL);
		}
		ft_check_n_fractionned(str, dest, 0);
	}
	else
	{
		dest = malloc((ft_strlen_gnl(str, 1) + 2) * sizeof(char));
		if (!dest)
		{
			*error = 1;
			return (NULL);
		}
		ft_check_n_fractionned(str, dest, 1);
	}
	return (dest);
}

char	*ft_clear_buff(char *buffer)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
		buffer[i++] = '\0';
	return (0);
}
