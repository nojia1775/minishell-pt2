/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:59:09 by nadjemia          #+#    #+#             */
/*   Updated: 2024/08/29 13:15:02 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	supp_pipe(t_token **tokens, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (tokens[i])
			tokens[i]->nbr_pipe--;
		if (tokens[i] == NULL)
			break ;
		i++;
	}
	while (i < len)
	{
		tokens[i] = tokens[i + 1];
		if (tokens[i])
			tokens[i]->nbr_pipe--;
		i++;
	}
}

int	len_tokens(t_token **tokens)
{
	int		len;

	len = 0;
	while (tokens[len])
		len++;
	return (len);
}

int	there_is_cmd(t_token *list)
{
	t_token	*cur;

	cur = list;
	while (cur->prev)
		cur = cur->prev;
	while (cur)
	{
		if (cur->type == CMD)
			return (1);
		cur = cur->next;
	}
	return (0);
}

static int	

// Rassemble l'env dans un double tab car execve prends comme
// argument un double tab (l'env)
char	**stock_total_env(t_list **envp, t_list **exp_var)
{
	int		len;
	int		i;
	t_list	*head;
	t_list	*current;
	char	**total_env;

	i = 0;
	head = *envp;
	current = *exp_var;
	len = ft_lstlen(envp) + ft_lstlen(exp_var) + 1;
	total_env = malloc(len * sizeof(char *));
	if (!total_env)
		return (NULL);
	if (envp && *envp)
	{
		while (head)
		{
			total_env[i] = ft_strdup(head->content);
			i++;
			head = head->next;
		}
	}
	if (exp_var && *exp_var)
	{
		while (current)
		{
			total_env[i] = ft_strdup(current->content);
			i++;
			current = current->next;
		}
	}
	total_env[i] = NULL;
	return (total_env);
}
