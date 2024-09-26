/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:59:35 by almichel          #+#    #+#             */
/*   Updated: 2024/09/26 09:18:34 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_return_strcat(char *dest, char *src, char *result)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (dest)
	{
		while (dest[i])
		{
			result[i] = dest[i];
			i++;
		}
	}
	if (src)
	{
		while (src[j])
		{
			result[i] = src[j];
			i++;
			j++;
		}	
	}
	result[i] = '\0';
	return (result);
}

char	*ft_str3cat(char *dest, char *src1, char *src2, char *total_setup)
{
	int		i;
	int		j;
	int		k;

	k = -1;
	j = -1;
	i = -1;
	if (dest)
		while (dest[++i])
			total_setup[i] = dest[i];
	if (src1)
	{
		while (src1[++j])
		{
			total_setup[i] = src1[j];
			i++;
		}
	}
	if (src2)
	{
		while (src2[++k])
			total_setup[i++] = src2[k];
	}
	total_setup[i] = '\0';
	return (total_setup);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
