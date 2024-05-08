/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upid_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:27:32 by almichel          #+#    #+#             */
/*   Updated: 2024/04/08 00:12:14 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_p(unsigned long n, int base)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		count = 1;
		return (count);
	}
	while (n)
	{
		n = n / base;
		count++;
	}
	return (count);
}

int	ft_count_di(int nb, int base)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
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

int	ft_itoa_di(int n, t_listt **list, int *error, int base)
{
	char		*result;
	int			count;
	long int	nb;
	int			i;
	t_listt		*new_case;

	nb = n;
	count = ft_count_di(nb, base);
	i = count;
	result = malloc((count + 1) * sizeof(char));
	if (!result)
		return (*error = 0);
	result = ft_tab_itoa(nb, result, count, base);
	new_case = ft_lstnew_two(result, i);
	ft_lstadd_backk(list, new_case);
	return (i);
}

int	ft_u(unsigned n, t_listt **list, int *error, int base)
{
	char		*result;
	int			count;
	long int	nb;
	int			i;
	t_listt		*new_case;

	nb = n;
	count = ft_count_p(n, base);
	i = count;
	result = malloc((count + 1) * sizeof(char));
	if (!result)
		return (*error = 0);
	result[count--] = '\0';
	if (nb == 0)
		result[0] = '0';
	while (nb > 0)
	{
		result[count--] = nb % base + 48;
		nb = nb / base;
	}
	new_case = ft_lstnew_two(result, i);
	ft_lstadd_backk(list, new_case);
	return (i);
}

int	ft_p(void *ptr, t_listt **list, int *error, int base)
{
	char			*result;
	int				count;
	unsigned long	n;
	t_listt			*new_case;
	int				i;

	if (!ptr)
	{
		result = ft_strdupp("(nil)");
		new_case = ft_lstnew_two(result, 5);
		ft_lstadd_backk(list, new_case);
		return (5);
	}
	n = (unsigned long)ptr;
	count = ft_count_p(n, base) + 2;
	result = malloc((count + 1) * sizeof(char));
	if (!result)
		return (*error == 0);
	i = count;
	result[count--] = '\0';
	result = ft_p_plus(result, base, n, count);
	new_case = ft_lstnew_two(result, i);
	ft_lstadd_backk(list, new_case);
	return (i);
}
