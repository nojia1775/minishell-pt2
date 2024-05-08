/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:12:33 by almichel          #+#    #+#             */
/*   Updated: 2024/04/22 16:59:28 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_lists(t_list **env, t_list **exp_var)
{
	t_list	*current;
	t_list	*head;

	current = *env;
	head = *exp_var;
	if (env && *env)
	{
		while (*env)
		{
			current = (*env)->next;
			free((*env)->content);
			free(*env);
			(*env) = current;
		}
	}
	if (exp_var && *exp_var)
	{
		while (*exp_var)
		{
			head = (*exp_var)->next;
			free((*exp_var)->content);
			free(*exp_var);
			(*exp_var) = head;
		}
	}
}

void	ft_putstr_msg(char *s, int fd, char *str)
{
	int		total;
	char	*error;

	error = ft_strjoin_error(str, s);
	total = ft_strlen(error);
	write(fd, error, total);
	free(error);
}

void	free_double_tabs(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
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
	len = ft_strlen(s1) + ft_strlen_space(s2) + 1;
	tab = malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[j++] = s1[i++];
	tab[j++] = '/';
	i = 0;
	while (s2[i] != ' ' && s2[i])
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}

