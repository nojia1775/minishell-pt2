/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <	almichel@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:56:39 by nadjemia          #+#    #+#             */
/*   Updated: 2024/05/08 14:37:31 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*init_index_of_var(char *str)
{
	int	count;
	int	i;
	int	*index;
	
	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == '$')
			count++;
	index = (int *)malloc(sizeof(int) * (count + 1));
	i = 0;
	while (i < count + 1)
		index[i++] = -1;
	return (index);
}

static void	var_to_val(char *dest, char *str, int *index_of_var, t_list **env, t_list **exp_var)
{
	int		i;
	int		y;
	int		count;
	int		z;
	char	*value;

	count = 0;
	i = 0;
	y = 0;
	while (str[i])
	{
		if (i == index_of_var[count])
		{
			value = get_env_value(str + i, env, exp_var);
			z = 0;
			if (value)
			{
				while (value[z])
					dest[y++] = value[z++];
			}
			i += word_len(&str[i]);
			count++;
		}
		else
			dest[y++] = str[i++];
	}
	dest[y] = '\0';
}

char	*interpretation(char *str, int *index_of_var, t_list **env,
	t_list **exp_var)
{
	int		total_len;
	char	*result;
	
	
	total_len = total_len_str(str, index_of_var, env, exp_var);
	if (total_len < 0)
		return (NULL);
	result = (char *)malloc(sizeof(char) * total_len + 1);
	if (!result)
		return (NULL);
	var_to_val(result, str, index_of_var, env, exp_var);
	free(index_of_var);
	return (result);
}
