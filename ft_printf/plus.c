/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:52:22 by almichel          #+#    #+#             */
/*   Updated: 2024/04/08 00:11:40 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_p_plus(char *result, int base, unsigned long n, int count)
{
	while (n > 0)
	{
		result[count--] = "0123456789abcdef"[n % base];
		n = n / base;
	}
	result[count] = 'x';
	count--;
	result[count] = '0';
	return (result);
}

int	ft_total_size_plus(t_listt *head, int totalsize)
{
	while (head)
	{
		totalsize = totalsize + head->size;
		head = head->next;
	}
	return (totalsize);
}
