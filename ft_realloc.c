/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:14:41 by noah              #+#    #+#             */
/*   Updated: 2024/07/24 12:41:38 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*tmp;

	tmp = ptr;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, tmp, size);
	free(tmp);
	return (ptr);
}