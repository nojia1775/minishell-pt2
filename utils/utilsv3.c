/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:12:33 by almichel          #+#    #+#             */
/*   Updated: 2024/09/02 13:50:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_lists(t_list *env, t_list *exp_var)
{
	t_list	*cur;
	t_list	*rm;

	cur = env;
	while (cur)
	{
		free(cur->content);
		rm = cur;
		cur = cur->next;
		free(rm);
	}
	env = NULL;
	cur = exp_var;
	while (cur)
	{
		free(cur->content);
		rm = cur;
		cur = cur->next;
		free(rm);
	}
	exp_var = NULL;
}

void	ft_putstr_msg(char *s, int fd, char *str)
{
	int		total;
	char	*error;

	error = ft_strjoin_error(str, s);
	total = ft_strlen(error);
	write(fd, "minishell: ", sizeof("minishell: "));
	write(fd, error, total);
	free(error);
}

char	*ft_strjoin_error(char const *s1, char const *s2)
{
	char	*tab;
	int		len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	tab = malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	while (s2[i])
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}

char	*ft_strjoin_cmd(char const *s1, char const *s2)
{
	char	*tab;
	int		len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	tab = malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[j++] = s1[i++];
	tab[j++] = '/';
	i = 0;
	while (s2[i])
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}
