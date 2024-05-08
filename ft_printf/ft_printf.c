/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:33:15 by almichel          #+#    #+#             */
/*   Updated: 2024/04/08 00:10:52 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_write_tab(char *tab, int size)
{
	write(1, tab, size);
	free(tab);
}

int	ft_stock_char(char c, t_listt **list, int *error)
{
	char	*tab;
	int		size;
	t_listt	*new_case;

	tab = malloc(2 * sizeof(char));
	if (!tab)
		return (*error == 0);
	size = 1;
	tab[0] = c;
	tab[1] = '\0';
	new_case = ft_lstnew_two(tab, size);
	ft_lstadd_backk(list, new_case);
	return (1);
}

int	ft_search_arg(char c, t_listt **list, va_list arg, int *error)
{
	int	size;

	size = 0;
	if (c == 'c')
		size = ft_c(va_arg(arg, int), list, error);
	else if (c == 's')
		size = ft_stock_string(va_arg(arg, char *), list, error);
	else if (c == 'p')
		size = ft_p(va_arg(arg, void *), list, error, 16);
	else if (c == 'd' || c == 'i')
		size = ft_itoa_di(va_arg(arg, int), list, error, 10);
	else if (c == 'u')
		size = ft_u(va_arg(arg, unsigned int), list, error, 10);
	else if (c == 'x')
		size = ft_itoa_n(va_arg(arg, unsigned int), list, error, 16);
	else if (c == 'X')
		size = ft_itoa_maj(va_arg(arg, unsigned int), list, error, 16);
	else if (c == '%')
		size = ft_c('%', list, error);
	return (size);
}

int	ft_prog_printf(const char *str, t_listt **list, va_list arg, int *error)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i] && *error == -1)
	{
		if (str[i] == '%')
		{
			size = size + ft_search_arg(str[i + 1], list, arg, error);
			i++;
		}
		else
			size = size + ft_stock_char(str[i], list, error);
		i++;
	}
	return (size);
}

int	ft_printf(const char *str, ...)
{
	int		size;
	va_list	va;
	int		error;
	char	*tab;
	t_listt	*list;

	list = NULL;
	error = -1;
	va_start(va, str);
	size = ft_prog_printf(str, &list, va, &error);
	va_end(va);
	tab = ft_list_to_tab(&list);
	if (error == 1)
		{
			size = -1;
			return (size);
		}
	ft_write_tab(tab, size);
	return (size);
}
