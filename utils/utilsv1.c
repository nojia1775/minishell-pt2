/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:59:35 by almichel          #+#    #+#             */
/*   Updated: 2024/04/15 17:41:49 by almichel         ###   ########.fr       */
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
	while (dest[i])
	{
		result[i] = dest[i];
		i++;
	}
	while (src[j])
	{
		result[i] = src[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}
char	*ft_str3cat(char *dest, char *src1, char *src2, char *total_setup)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	j = 0;
	i = 0;
	while (dest[i])
	{
		total_setup[i] = dest[i];
		i++;
	}	
	while (src1[j])
	{
		total_setup[i] = src1[j];
		i++;
		j++;
	}
	while (src2[k])
	{
		total_setup[i] = src2[k];
		i++;
		k++;
	}
	total_setup[i] = '\0';
	return (total_setup);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
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
