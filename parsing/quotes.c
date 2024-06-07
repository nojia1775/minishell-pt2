/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:48:20 by nadjemia          #+#    #+#             */
/*   Updated: 2024/06/07 22:29:43 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	ptr_on_quotes2(int *in_quotes, char *c)
// {
// 	int	i;
	
// 	(void)c;
// 	i = -1;
// 	if (!(*in_quotes))
// 		*in_quotes = 1;
// 	else
// 		*in_quotes = 0;
// 	while (c[++i])
// 		c[i] = c[i + 1];
// }

/*static void	is_interpreted(char *str, int *i, int *index, int *count, t_list **env, t_list **exp_var)
{
	char	*value;
	int		x;
	
	value = get_env_value(str, env, exp_var);
	if (value)
		index[(*count)++] = (*i)++;
	else
	{
		while (str[0] != ' ' && str[0] != 39 && str[0] != 34
			&& str[0] != '\t' && str[0])
		{
			x = -1;
			while (str[++x])
				str[x] = str[x + 1];
		}
		if (str[0] != 39 && str[0] != 34)
			(*i)++;
	}
}

static void	trim_quotes(char *str, int *in_single, int *in_double,
			int *index_of_var, t_list **env, t_list **exp_var)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 && !(*in_single))
			i++;
			//ptr_on_quotes2(in_double, &str[i]);
		else if (str[i] == 39 && !(*in_double))
			i++;
			//ptr_on_quotes2(in_single, &str[i]);
		else if (str[i] == '$' && !(*in_single) && (ft_isalnum(str[i + 1])
			|| str[i + 1] == '_'))
			is_interpreted(str + i, &i, index_of_var, &count, env, exp_var);
		else
			i++;
	}
}

static char	*rm_quotes(char *str, t_list **env, t_list **exp_var, t_token **tokens)
{
	int		*index_of_var;
	int		in_double;
	int		in_single;
	char	*result;
	
	(void)tokens;
	in_double = 0;
	in_single = 0;
	index_of_var = init_index_of_var(str);
	if (!index_of_var)
		return (NULL);
	trim_quotes(str, &in_single, &in_double, index_of_var, env, exp_var);
	int i = 0;
	while (index_of_var[i] != -1)
		printf("%d\n", index_of_var[i++]);
	result = interpretation(str, index_of_var, env, exp_var);
	if (!result)
		return (NULL);
	return (result);
}

char	*quotes(char *str, t_list **env, t_list **exp_var, t_token **tokens)
{
	char	*result;
	
	str = ft_strtrim(str, " ");
	rm_space(str);
	if (!nbr_quotes(str))
		return (NULL);
	result = rm_quotes(str, env, exp_var, tokens);
	free(str);
	result = ft_strtrim(result, " ");
	if (!result)
		return (NULL);
	return (result);
}*/
