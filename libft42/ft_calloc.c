/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:29:27 by almichel          #+#    #+#             */
/*   Updated: 2024/08/29 11:22:06 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t		sum;
	char		*dest;
	int			i;

	i = 0;
	if (nmemb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	if (SIZE_MAX / nmemb < size)
		return (NULL);
	sum = nmemb * size;
	dest = malloc(sum);
	if (!dest)
		return (NULL);
	while (sum--)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}
