/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xx_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:25:21 by almichel          #+#    #+#             */
/*   Updated: 2024/04/08 00:12:26 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_x(unsigned int nb, int base)
{
	int	count;

	count = 0;
	if (nb == 0)
	{
		count = 1;
		return (count);
	}
	while (nb)
	{
		nb = nb / base;
		count++;
	}
	return (count);
}

int	ft_itoa_n(unsigned int n, t_listt **list, int *error, int base)
{
	char		*result;
	int			count;
	long int	nb;
	int			i;
	t_listt		*new_case;

	nb = n;
	count = ft_count_x(nb, base);
	i = count;
	result = malloc((count + 1) * sizeof(char));
	if (!result)
		return (*error == 0);
	result = ft_tab_itoa(nb, result, count, base);
	new_case = ft_lstnew_two(result, i);
	ft_lstadd_backk(list, new_case);
	return (i);
}

char	*ft_min_to_maj(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

int	ft_itoa_maj(unsigned int n, t_listt **list, int *error, int base)
{
	char		*result;
	int			count;
	long int	nb;
	int			i;
	t_listt		*new_case;

	nb = n;
	count = ft_count_x(n, base);
	i = count;
	result = malloc((count + 1) * sizeof(char));
	if (!result)
		return (*error == 0);
	result = ft_tab_itoa(nb, result, count, base);
	result = ft_min_to_maj(result);
	new_case = ft_lstnew_two(result, i);
	ft_lstadd_backk(list, new_case);
	return (i);
}

char	*ft_tab_itoa(long int nb, char *result, int count, int base)
{
	result[count--] = '\0';
	if (nb == 0)
		result[0] = '0';
	if (nb < 0)
	{
		nb = -nb;
		result[0] = '-';
	}
	while (nb > 0)
	{
		result[count--] = "0123456789abcdef"[nb % base];
		nb = nb / base;
	}
	return (result);
}
