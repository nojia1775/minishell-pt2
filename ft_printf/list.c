/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:23:33 by almichel          #+#    #+#             */
/*   Updated: 2024/04/13 22:57:12 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_listt	*ft_lstnew_two(char *str, int size)
{
	t_listt	*list;

	list = malloc(sizeof(t_listt));
	if (!list)
		return (NULL);
	list->content = str;
	list->size = size;
	list->next = NULL;
	return (list);
}

void	ft_lstadd_backk(t_listt **lst, t_listt *new)
{
	t_listt	*last;

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

void	ft_free_list(t_listt **list)
{
	t_listt	*head;
	t_listt	*temp;

	head = *list;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
	}
}

void	ft_strcpy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_list_to_tab(t_listt **list)
{
	t_listt	*head;
	char	*tab;
	int		totalsize;
	char	*temp;

	head = *list;
	totalsize = 0;
	totalsize = ft_total_size_plus(head, totalsize);
	tab = malloc((totalsize + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	tab[0] = '\0';
	head = *list;
	temp = tab;
	while (head)
	{
		ft_strcpy(tab, head->content, head->size);
		tab = tab + head->size;
		head = head->next;
	}
	tab = temp;
	tab[totalsize] = '\0';
	ft_free_list(list);
	return (tab);
}
