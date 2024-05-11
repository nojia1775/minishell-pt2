/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:52:04 by nadjemia          #+#    #+#             */
/*   Updated: 2024/05/11 11:26:43 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	valid_char(char *str)
{
	int		i;
	int		j;
	int		in_single;
	int		in_double;
	char	*charset;

	charset = "&;:!#@*";
	i = 0;
	in_double = 0;
	in_single = 0;
	while (str[i])
	{
		if (str[i] == 34 && !in_single)
			in_double = (in_double + 1) % 2;
		if (str[i] == 39 && !in_double)
			in_single = (in_single + 1) % 2;
		j = 0;
		while (charset[j])
			if (str[i] == charset[j++] && !in_double && !in_single)
				return (str[i]);
		i++;
	}
	return ('o');
}

char	*find_var(char *str, t_list **env, t_list **exp_var)
{
	char	**total_env;
	int		i;
	char	*str2;
	char	*str3;
	
	str2 = NULL;
	i = 0;
	total_env = stock_total_env(env, exp_var);
	while (total_env[i])
	{
		str3 = ft_strjoin(str, "=");
		if (ft_strncmp(str3, total_env[i], ft_strlen(str) + 1) == 0)
			str2 = ft_strdup(total_env[i]);
		i++;
		free(str3);
	}
	i = 0;
	while (total_env[i])
		free(total_env[i++]);
	free(total_env);
	if (!str2)
		return (NULL);
	return (str2 + ft_strlen_egal(str2) + 1);
}

int	parsing(char **input, t_list **env, t_list **exp_var)
{
	char	*result;
	// int	nbr_tokens;
	// t_token	**tokens;
	
	if (valid_char(*input) != 'o')
		return (printf("minishell : unknown charactere '%c'\n",
			valid_char(*input)));	
	if (!conform_pipe(*input))
		return (printf("minishell : Syntax error\n"), 0);
	// nbr_tokens = count_pipe(*input) + 1;
	// tokens = (t_token **)malloc(sizeof(t_token *) * (nbr_tokens + 1));
	// if (!tokens)
	// 	return (0);
	// tokens[nbr_tokens] = NULL;
	result = quotes(*input, env, exp_var);
	if (!result)
		return (printf("minishell : Syntax error\n"), 0);
	*input = result;
	printf("%s\n", result);
	return (1);
}
