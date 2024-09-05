/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:13:15 by almichel          #+#    #+#             */
/*   Updated: 2024/09/05 12:17:20 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strcpy_(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int	ft_strlen_quotes(const char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			count++;
		i++;
	}
	return (count);
}

char	*ft_strdup_quotes(const char *s)
{
	int		i;
	char	*s2;
	int		size;
	int		j;

	j = 0;
	i = 0;
	size = ft_strlen_quotes(s);
	s2 = malloc((size + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i++;
		else
		{
			s2[j] = s[i];
			i++;
			j++;
		}
	}
	s2[j] = '\0';
	return (s2);
}

char	*ft_strdup_outside_quotes(const char *s)
{
	int		i;
	char	*s2;
	int		size;
	int		j;
	char	stock_char;

	j = 0;
	i = 0;
	size = ft_strlen_quotes(s) + 2;
	s2 = malloc((size + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	while (s[i] && (s[i] == '\'' || s[i] == '"'))
		i++;
	i--;
	s2[j] = s[i];
	stock_char = s[i];
	i++;
	j++;
	while (s[i] != '\'' && s[i] != '"' && s[i])
		s2[j++] = s[i++];
	s2[j] = stock_char;
	j++;
	s2[j] = '\0';
	return (s2);
}

int	checking_if_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
			i++;
		else
			return (-1);
	}
	return (1);
}
