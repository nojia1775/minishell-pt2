/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:37:45 by nadjemia          #+#    #+#             */
/*   Updated: 2024/07/16 12:23:23 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	word_len(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != ' ' && str[i] != 39 && str[i] != 34
		&& str[i] && str[i] != '\t')
	{
		i++;
		if (str[i] == '$')
			return (count + 1);
		count++;
	}
	return (count);
}

char	*get_env_value(char *str, t_list **env, t_list **exp_var)
{
	char	*var;
	char	*value;
	char	*result;
	int		len;

	len = word_len(str);
	var = (char *)malloc(sizeof(char) * len);
	if (!var)
		return (NULL);
	ft_strlcpy(var, str + 1, len + 1);
	var[len - 1] = '\0';
	result = ft_strtrim(var, " ");
	value = find_var(result, env, exp_var);
	free(var);
	free(result);
	if (!value)
		return (NULL);
	return (value);
}

int	total_len_str(char *str, int *index_of_var, t_list **env, t_list **exp_var)
{
	int	count;
	int	i;
	char	*value;

	count = ft_strlen(str);
	i = 0;
	while (index_of_var[i] != -1)
	{
		count -= word_len(&str[index_of_var[i]]);
		value = get_env_value(&str[index_of_var[i]], env, exp_var);
		if (value)
			count += ft_strlen(value);
		i++;
	}
	return (count);
}

static void	is_in_quotes(int *in_quote)
{
	if (!(*in_quote))
		*in_quote = 1;
	else
		*in_quote = 0;
}

void	rm_space(char *str)
{
	int	i;
	int	l;
	int	in_sgl;
	int	in_dbl;
	
	i = 0;
	in_sgl = 0;
	in_dbl = 0;
	while (str[i])
	{
		if (str[i] == 34 && !in_sgl)
			is_in_quotes(&in_dbl);
		if (str[i] == 39 && !in_dbl)
			is_in_quotes(&in_sgl);
		l = i - 1;
		if (str[i] == ' ' && str[i + 1] == ' ' && !in_dbl && !in_sgl)
		{
			while (str[++l])
				str[l] = str[l + 1];
		}
		else 
			i++;
	}
}
